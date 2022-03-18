#include "visuals.hpp"
#include "../lagcomp/lagcomp.hpp"
#include "../movement/movement.hpp"

#include <algorithm>
#include <codecvt>
#include <locale>

sdk::box visuals::esp_box::calculate_box( sdk::c_tf_player* player, bool& on_screen )
{
	auto& player_info = g_entity_list.players[ player->entindex( ) ];

	sdk::vector mins = player_info.mins;
	sdk::vector maxs = player_info.maxs;

	sdk::matrix_3x4 transform = player_info.rgfl;

	sdk::vector points[] = { sdk::vector( mins.x, mins.y, mins.z ), sdk::vector( mins.x, maxs.y, mins.z ), sdk::vector( maxs.x, maxs.y, mins.z ),
		                     sdk::vector( maxs.x, mins.y, mins.z ), sdk::vector( maxs.x, maxs.y, maxs.z ), sdk::vector( mins.x, maxs.y, maxs.z ),
		                     sdk::vector( mins.x, mins.y, maxs.z ), sdk::vector( maxs.x, mins.y, maxs.z ) };

	sdk::vector translated_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ )
		translated_points[ iterator ] = math::vector_transform( points[ iterator ], transform );

	sdk::vector screen_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ ) {
		bool buffer_on_screen = true;

		auto& screen_point = screen_points[ iterator ];

		screen_point = utilities::world_to_screen( translated_points[ iterator ], buffer_on_screen );

		if ( buffer_on_screen && !( screen_point.x < 0 ) && !( screen_point.y < 0 ) && !( screen_point.x > g_globals.screen_size.x ) &&
		     !( screen_point.y > g_globals.screen_size.y ) )
			on_screen = true;
	}

	float top    = screen_points[ 0 ].y;
	float left   = screen_points[ 0 ].x;
	float right  = screen_points[ 0 ].x;
	float bottom = screen_points[ 0 ].y;

	for ( int iterator = 1; iterator < 8; iterator++ ) {
		if ( left > screen_points[ iterator ].x )
			left = screen_points[ iterator ].x;
		if ( top > screen_points[ iterator ].y )
			top = screen_points[ iterator ].y;
		if ( right < screen_points[ iterator ].x )
			right = screen_points[ iterator ].x;
		if ( bottom < screen_points[ iterator ].y )
			bottom = screen_points[ iterator ].y;
	}

	return sdk::box( ROUND_UP( left ), ROUND_UP( top ), ROUND_UP( right ), ROUND_UP( bottom ) );
}

void visuals::impl::update_object( esp_object& object )
{
	if ( !object.owner || !object.owner->entindex( ) )
		return;

	if ( !object.owner->name( ).data( ) )
		return;

	auto& dormant_info = g_entity_list.players[ object.owner->entindex( ) ].dormant_info;
	auto dormant_time  = ticks_to_time( g_interfaces.globals->tick_count - dormant_info.found_tick );

	if ( dormant_time < 2.5f )
		dormant_time = 0.f;

	auto dormant_alpha_modulation = dormant_info.valid ? -( ( dormant_time - 2.5f ) / .5f ) + 1.f : 1.f;

	object.box.cornered     = false;
	object.box.outline[ 0 ] = true;
	object.box.outline[ 1 ] = true;
	object.box.draw         = false;
	object.box.skeleton     = false;
	object.box.backtrack    = false; // very crashy right now.

	object.box.color = sdk::color( 255, 255, 255, 255 * dormant_alpha_modulation );

	object.box.titles.clear( );
	object.box.texts.clear( );
	object.box.bars.clear( );

	auto text_name = esp_text( );

	auto health_bar  = esp_bar( );
	auto health_text = esp_text( );

	auto weapon_ammo_bar  = esp_bar( );
	auto weapon_name_text = esp_text( );

	text_name.location = esp_location::LOCATION_TOP;
	text_name.text     = object.owner->name( );
	text_name.color    = sdk::color( 255, 255, 255, 255 * dormant_alpha_modulation );
	text_name.font     = g_fonts[ fnv( "esp_font" ) ];
	text_name.flags    = font_flags::FLAG_DROPSHADOW;

	object.box.texts.push_back( text_name );

	health_bar.location   = esp_location::LOCATION_LEFT;
	health_bar.width      = 2;
	health_bar.color_from = sdk::color( 0, 255, 0, 255 * dormant_alpha_modulation );
	health_bar.color_to   = sdk::color( 255, 0, 0, 255 * dormant_alpha_modulation );
	health_bar.min        = 0;
	health_bar.max        = object.owner->max_health( );
	health_bar.cur =
		health_bar.max > 0 ? std::clamp( object.owner->health( ), 0, static_cast< int >( health_bar.max ) ) : object.owner->max_health( );

	object.box.bars.push_back( health_bar );

	health_text.location = esp_location::LOCATION_LEFT;
	health_text.text     = std::to_string( object.owner->health( ) );
	health_text.color    = sdk::color( 255, 255, 255, 255 * dormant_alpha_modulation );
	health_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
	health_text.flags    = font_flags::FLAG_OUTLINE;

	object.box.texts.push_back( health_text );

	auto& player_info = g_entity_list.players[ object.owner->entindex( ) ];

	if ( player_info.bot ) {
		auto bot_text = esp_text( );

		bot_text.location = esp_location::LOCATION_RIGHT;
		bot_text.text     = "BOT";
		bot_text.color    = sdk::color( 255, 255, 255, 255 * dormant_alpha_modulation );
		bot_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		bot_text.flags    = font_flags::FLAG_OUTLINE;

		object.box.texts.push_back( bot_text );
	}

	if ( player_info.condition & sdk::tf_cond_ubercharged ) {
		auto uber_text = esp_text( );

		uber_text.location = esp_location::LOCATION_RIGHT;
		uber_text.text     = "UBER";
		uber_text.color    = sdk::color( 173, 216, 230, 255 * dormant_alpha_modulation );
		uber_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		uber_text.flags    = font_flags::FLAG_OUTLINE;

		object.box.texts.push_back( uber_text );
	}

	if ( player_info.condition & sdk::tf_cond_bleeding ) {
		auto bleed_text = esp_text( );

		bleed_text.location = esp_location::LOCATION_RIGHT;
		bleed_text.text     = "BLEED";
		bleed_text.color    = sdk::color( 255, 204, 203, 255 * dormant_alpha_modulation );
		bleed_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		bleed_text.flags    = font_flags::FLAG_OUTLINE;

		object.box.texts.push_back( bleed_text );
	}

	if ( player_info.condition & sdk::tf_cond_bonked ) {
		auto bonk_text = esp_text( );

		bonk_text.location = esp_location::LOCATION_RIGHT;
		bonk_text.text     = "BONK";
		bonk_text.color    = sdk::color( 255, 235, 203, 255 * dormant_alpha_modulation );
		bonk_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		bonk_text.flags    = font_flags::FLAG_OUTLINE;

		object.box.texts.push_back( bonk_text );
	}

	if ( player_info.condition & sdk::tf_cond_mini_crits ) {
		auto mini_crits_text = esp_text( );

		mini_crits_text.location = esp_location::LOCATION_RIGHT;
		mini_crits_text.text     = "CRIT";
		mini_crits_text.color    = sdk::color( 255, 235, 203, 255 * dormant_alpha_modulation );
		mini_crits_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		mini_crits_text.flags    = font_flags::FLAG_OUTLINE;

		object.box.texts.push_back( mini_crits_text );
	}

	auto player_weapon = g_interfaces.entity_list->get< sdk::c_tf_weapon_base >( object.owner->active_weapon( ) );

	if ( player_weapon ) {
		auto weapon_info = player_weapon->get_weapon_info( );

		// TF2 Weapons are just too buggy to even touch. Unlike CS:GO, localization doesn't work.
		//
		//		weapon_ammo_bar.location   = esp_location::LOCATION_BOTTOM;
		//		weapon_ammo_bar.width      = 2;
		//		weapon_ammo_bar.color_from = sdk::color( 173, 216, 230, 255 * dormant_alpha_modulation );
		//		weapon_ammo_bar.color_to   = sdk::color( 173, 216, 230, 255 * dormant_alpha_modulation );
		//		weapon_ammo_bar.min        = 0;
		//		weapon_ammo_bar.max        = weapon_info.max_clip1;
		//		weapon_ammo_bar.cur        = player_weapon->clip1( );
		//
		//		object.box.bars.push_back( weapon_ammo_bar );

		//		if ( auto weapon_name = g_interfaces.localize->find( weapon_info.class_name ) ) {
		//			size_t localize_size{ };
		//			char localize_name[ 2048 ]{ };
		//
		//			wcstombs_s( &localize_size, localize_name, weapon_name, sizeof( localize_name ) );

		//		weapon_name_text.location = esp_location::LOCATION_BOTTOM;
		//		weapon_name_text.text     = std::string( weapon_info.class_name );
		//		weapon_name_text.color    = sdk::color( 255, 255, 255, 255 * dormant_alpha_modulation );
		//		weapon_name_text.font     = g_fonts[ fnv( "esp_indicator_font" ) ];
		//		weapon_name_text.flags    = font_flags::FLAG_OUTLINE;
		//
		//		object.box.texts.push_back( weapon_name_text );
		//		}
	}
}

void visuals::impl::update( )
{
	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index );

		if ( ( !player_info.valid && !player_info.dormant_info.valid ) || !player )
			continue;

		esp_object& buffer_object = esp_objects[ player_info.index ];

		buffer_object.owner = player;

		if ( true )
			update_object( buffer_object );
	}
}

void visuals::impl::render( )
{
	if ( !g_interfaces.engine_client->is_connected( ) || !g_globals.local )
		return;

	update( );

	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index );

		if ( ( !player_info.valid && !player_info.dormant_info.valid ) || !player )
			continue;

		esp_object& object = esp_objects[ player_info.index ];

		//		player->draw_client_hitbox( g_interfaces.globals->frame_time * 2 );
		object.box.render( player );
	}

	auto net_channel = g_interfaces.net_channel;

	if ( !net_channel )
		return;

	auto shiftable_ticks = g_globals.stored_ticks;

	auto indicator_font = g_fonts[ fnv( "indicator_verdana_font" ) ];
	auto formatted_text = std::format( "DT: {}", shiftable_ticks );
	auto distance       = 120.f * ( shiftable_ticks / 24.f );
	auto lerped_color   = sdk::hsv( distance, 100.f, 70.f ).to_color( );

	g_render.render_text( { 10, g_globals.screen_size.y / 2 }, font_alignment::AL_VERTICAL_CENTER, font_flags::FLAG_DROPSHADOW,
	                      formatted_text.c_str( ), indicator_font, lerped_color );
}

void visuals::esp_box::render( sdk::c_tf_player* owner )
{
	bool on_screen  = false;
	auto dimensions = calculate_box( owner, on_screen );
	auto position   = sdk::vector( static_cast< int >( dimensions.x ), static_cast< int >( dimensions.y ) );
	auto size       = sdk::vector( static_cast< int >( dimensions.w ), static_cast< int >( dimensions.h ) ) - position;

	if ( !on_screen )
		return;

	if ( draw ) {
		// outer outline
		if ( outline[ 0 ] )
			g_render.render_rectangle( position - sdk::vector( 1, 1 ), size + sdk::vector( 2, 2 ), sdk::color( 0, 0, 0, color.a ) );
		// inner outline
		if ( outline[ 1 ] )
			g_render.render_rectangle( position + sdk::vector( 1, 1 ), size - sdk::vector( 2, 2 ), sdk::color( 0, 0, 0, color.a ) );

		g_render.render_rectangle( position, size, color );
	}

	if ( skeleton ) {
		if ( auto studio = g_interfaces.model_info->get_studio_model( owner->get_model( ) ) ) {
			for ( int bone_index = 0; bone_index < studio->num_bones; bone_index++ ) {
				auto bone = studio->get_bone( bone_index );

				if ( !bone || !( bone->flags & 0x100 ) || bone->parent == -1 )
					continue;

				auto parent_bone_index = bone->parent;

				sdk::vector parent_bone_screen{ }, bone_screen{ };

				bool bone_screen_on_screen   = true;
				bool parent_screen_on_screen = true;

				parent_bone_screen = utilities::world_to_screen( owner->get_bone_position( parent_bone_index ), bone_screen_on_screen );
				bone_screen        = utilities::world_to_screen( owner->get_bone_position( bone_index ), parent_screen_on_screen );

				if ( !bone_screen_on_screen || !parent_screen_on_screen )
					continue;

				g_render.render_line( parent_bone_screen.x, parent_bone_screen.y, bone_screen.x, bone_screen.y, { 255, 255, 255 } );
			}
		}
	}

	if ( backtrack ) {
		if ( g_lagcomp.heap_records[ owner->entindex( ) ] ) {
			static auto unlag_pointer = g_interfaces.cvar->find_var( "sv_maxunlag" );
			auto sv_maxunlag          = unlag_pointer->get_float( );
			auto sv_maxunlag_ticks    = time_to_ticks( sv_maxunlag );

			int last_valid_heap_record   = 0;
			float lowest_simulation_time = FLT_MAX;

			int first_valid_heap_record   = 0;
			float highest_simulation_time = 0;

			for ( int current_heap_iterator = 0; current_heap_iterator < sv_maxunlag_ticks; current_heap_iterator++ ) {
				lagcomp::record* current_record = &g_lagcomp.heap_records[ owner->entindex( ) ][ current_heap_iterator ];

				if ( !current_record )
					continue;

				if ( current_record->simulation_time < highest_simulation_time )
					continue;

				if ( !current_record->valid )
					continue;

				first_valid_heap_record = current_heap_iterator;
				highest_simulation_time = current_record->simulation_time;
			}

			for ( int current_heap_iterator = 0; current_heap_iterator < sv_maxunlag_ticks; current_heap_iterator++ ) {
				lagcomp::record* current_record = &g_lagcomp.heap_records[ owner->entindex( ) ][ current_heap_iterator ];

				if ( !current_record )
					continue;

				if ( current_record->simulation_time > lowest_simulation_time )
					continue;

				if ( !current_record->valid )
					continue;

				last_valid_heap_record = current_heap_iterator;
				lowest_simulation_time = current_record->simulation_time;
			}

			lagcomp::record current_record = g_lagcomp.heap_records[ owner->entindex( ) ][ last_valid_heap_record ];
			lagcomp::record last_record    = g_lagcomp.heap_records[ owner->entindex( ) ][ first_valid_heap_record ];

			if ( current_record.player ) {
				if ( auto studio = g_interfaces.model_info->get_studio_model( owner->get_model( ) ) ) {
					for ( int bone_index = 0; bone_index < studio->num_bones; bone_index++ ) {
						auto bone = studio->get_bone( bone_index );

						if ( !bone || !( bone->flags & 0x100 ) || bone->parent == -1 )
							continue;

						auto parent_bone_index = bone->parent;

						sdk::vector parent_bone_screen{ }, bone_screen{ };

						parent_bone_screen = utilities::world_to_screen( owner->get_bone_position( parent_bone_index, current_record.bone_matrix ) );
						bone_screen        = utilities::world_to_screen( owner->get_bone_position( bone_index, current_record.bone_matrix ) );

						g_render.render_line( parent_bone_screen.x, parent_bone_screen.y, bone_screen.x, bone_screen.y, { 255, 255, 255, 150 } );
					}
				}
			}
			if ( last_record.player ) {
				if ( auto studio = g_interfaces.model_info->get_studio_model( owner->get_model( ) ) ) {
					for ( int bone_index = 0; bone_index < studio->num_bones; bone_index++ ) {
						auto bone = studio->get_bone( bone_index );

						if ( !bone || !( bone->flags & 0x100 ) || bone->parent == -1 )
							continue;

						auto parent_bone_index = bone->parent;

						sdk::vector parent_bone_screen{ }, bone_screen{ };

						parent_bone_screen = utilities::world_to_screen( owner->get_bone_position( parent_bone_index, last_record.bone_matrix ) );
						bone_screen        = utilities::world_to_screen( owner->get_bone_position( bone_index, last_record.bone_matrix ) );

						g_render.render_line( parent_bone_screen.x, parent_bone_screen.y, bone_screen.x, bone_screen.y, { 255, 255, 255, 150 } );
					}
				}
			}
		}
	}

	float offset_x[ 4 ]{ };
	float offset_y[ 4 ]{ };

	for ( auto& bar : bars )
		bar.render( dimensions, offset_x[ static_cast< unsigned int >( bar.location ) ], offset_y[ static_cast< unsigned int >( bar.location ) ] );

	for ( auto& title : titles )
		title.render( dimensions, offset_x[ static_cast< unsigned int >( title.location ) ],
		              offset_y[ static_cast< unsigned int >( title.location ) ] );

	for ( auto& text : texts )
		text.render( dimensions, offset_x[ static_cast< unsigned int >( text.location ) ], offset_y[ static_cast< unsigned int >( text.location ) ] );
}

void visuals::esp_title::render( sdk::box box, float& offset_x, float& offset_y )
{
	auto text_size_buffer = g_render.render_text_size( text.c_str( ), font );
	auto text_size        = sdk::vector( text_size_buffer.x, text_size_buffer.y );

	sdk::vector position;

	switch ( location ) {
	case esp_location::LOCATION_TOP:
		break;
	case esp_location::LOCATION_LEFT:
		break;
	case esp_location::LOCATION_BOTTOM:
		break;
	case esp_location::LOCATION_RIGHT:
		break;
	}

	g_render.render_filled_rectangle( position, sdk::vector( text_size.x + 5, text_size.y + 4 ), sdk::color( 0, 0, 0, color.a * 0.7 ) );
	g_render.render_filled_rectangle( position, sdk::vector( 1, text_size.y + 4 ), color );

	g_render.render_text( position + sdk::vector( 3, 2 ), font_alignment::AL_DEFAULT, flags, text.c_str( ), font, sdk::color( 255, 255, 255, 255 ) );
}

void visuals::esp_text::render( sdk::box box, float& offset_x, float& offset_y )
{
	auto text_size_buffer = g_render.render_text_size( text.c_str( ), font );
	auto text_size        = sdk::vector( text_size_buffer.x, text_size_buffer.y );

	sdk::vector position;

	switch ( location ) {
	case esp_location::LOCATION_TOP:
		position.x = ( box.x + box.width( ).x / 2 ) - text_size.x / 2;
		position.y = ( box.y - text_size.y ) - 1;

		position.y -= offset_y;

		offset_y += text_size.y;
		break;
	case esp_location::LOCATION_BOTTOM:
		position.x = ( box.x + box.width( ).x / 2 ) - text_size.x / 2;
		position.y = box.h + 1;

		position.y += offset_y;

		offset_y += text_size.y;
		break;
	case esp_location::LOCATION_LEFT:
		position.x = ( box.x - text_size.x ) - 3;
		position.y = box.y;

		position.x -= offset_x;
		position.y += offset_y;

		offset_x += text_size.x;
		break;
	case esp_location::LOCATION_RIGHT:
		position.x = box.w + 2;
		position.y = box.y;

		position.x += offset_x;
		position.y += offset_y;

		offset_x += text_size.x;
		break;
	}

	g_render.render_text( position, font_alignment::AL_DEFAULT, flags, text.c_str( ), font, color );
}

void visuals::esp_bar::render( sdk::box box, float& offset_x, float& offset_y )
{
	sdk::vector border_start_position;
	sdk::vector border_end_position;

	sdk::vector start_position;
	sdk::vector end_position;

	auto current_percentage = -( cur / ( max - min ) ) + 1.f;
	auto current_color      = color_from.lerp( color_to, current_percentage );

	switch ( location ) {
	case esp_location::LOCATION_TOP:
		border_start_position.x = box.x;
		border_start_position.y = box.y - 3 - width;

		border_end_position.x = box.w + 2;
		border_end_position.y = box.y - 2;

		start_position.x = box.x + ( box.w - box.x ) * current_percentage;
		start_position.y = box.y - 3 - width;

		end_position.x = box.w + 1;
		end_position.y = box.y - 3;

		border_start_position.x += offset_x;
		border_start_position.y += offset_y;

		border_end_position.x += offset_x;
		border_end_position.y += offset_y;

		start_position.x += offset_x;
		start_position.y += offset_y;

		end_position.x += offset_x;
		end_position.y += offset_y;

		offset_y += 5;
		break;
	case esp_location::LOCATION_LEFT:
		border_start_position.x = box.x - 3 - width;
		border_start_position.y = box.y;

		border_end_position.x = box.x - 2;
		border_end_position.y = box.h + 2;

		start_position.x = box.x - 3 - width;
		start_position.y = box.y + ( box.h - box.y ) * current_percentage;

		end_position.x = box.x - 3;
		end_position.y = box.h + 1;

		border_start_position.x += offset_x;
		border_start_position.y += offset_y;

		border_end_position.x += offset_x;
		border_end_position.y += offset_y;

		start_position.x += offset_x;
		start_position.y += offset_y;

		end_position.x += offset_x;
		end_position.y += offset_y;

		offset_x += 3 + width;
		break;
	case esp_location::LOCATION_BOTTOM:
		border_start_position.x = box.x;
		border_start_position.y = box.h + 4;

		border_end_position.x = box.w + 2;
		border_end_position.y = box.h + 5 + width;

		start_position.x = box.x + ( box.w - box.x ) * current_percentage;
		start_position.y = box.h + 4;

		end_position.x = box.w + 1;
		end_position.y = box.h + 4 + width;

		border_start_position.x += offset_x;
		border_start_position.y += offset_y;

		border_end_position.x += offset_x;
		border_end_position.y += offset_y;

		start_position.x += offset_x;
		start_position.y += offset_y;

		end_position.x += offset_x;
		end_position.y += offset_y;

		offset_y += 5;
		break;
	case esp_location::LOCATION_RIGHT:
		border_start_position.x = box.w + 4;
		border_start_position.y = box.y;

		border_end_position.x = box.w + 5 + width;
		border_end_position.y = box.h + 2;

		start_position.x = box.w + 4;
		start_position.y = box.y + ( box.h - box.y ) * current_percentage;

		end_position.x = box.w + 4 + width;
		end_position.y = box.h + 1;

		border_start_position.x += offset_x;
		border_start_position.y += offset_y;

		border_end_position.x += offset_x;
		border_end_position.y += offset_y;

		start_position.x += offset_x;
		start_position.y += offset_y;

		end_position.x += offset_x;
		end_position.y += offset_y;

		offset_x += 3 + width;
		break;
	}

	g_render.render_filled_rectangle( border_start_position - sdk::vector( 1, 1 ),
	                                  border_end_position + sdk::vector( 2, 2 ) - border_start_position - sdk::vector( 1, 1 ),
	                                  sdk::color( 32, 32, 32, std::clamp( current_color.a - 50, 0, 255 ) ) );
	g_render.render_filled_rectangle( start_position, end_position - start_position, current_color );
}
