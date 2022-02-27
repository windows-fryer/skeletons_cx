#include "end_scene.hpp"
#include "../../../features/visuals/visuals.hpp"
#include "../../../sdk/structs/c_view_setup.hpp"

long hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto multi_core_rendering = _ReturnAddress( );

	if ( multi_core_rendering != _ReturnAddress( ) )
		return end_scene_hook.call_original( device );

	g_globals.screen_size = { static_cast< float >( g_render.get_viewport( ).Width ), static_cast< float >( g_render.get_viewport( ).Height ) };

	if ( sdk::c_view_setup view_setup; g_interfaces.base_client->get_player_view( view_setup ) ) {
		sdk::view_matrix world_to_view, view_to_projection, world_to_pixels;

		g_interfaces.render_view->get_matrices_for_view( view_setup, &world_to_view, &view_to_projection, &g_globals.view_matrix, &world_to_pixels );
	}

	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index );

		if ( ( !player_info.valid && !player_info.dormant_info.valid ) || !player )
			continue;

		visuals::esp_object& object = g_visuals.esp_objects[ player->entindex( ) ];

		if ( object.owner != player )
			continue;

		sdk::vector old_origin = player->get_abs_origin( );

		if ( !player_info.valid && ticks_to_time( g_interfaces.globals->tick_count - player_info.dormant_info.found_tick ) < 3.f ) {
			player->set_abs_origin( ticks_to_time( g_interfaces.globals->tick_count - player_info.dormant_info.vouchable_tick ) < 3.f
			                            ? player_info.dormant_info.vouchable_position
			                            : player_info.dormant_info.last_position );
			player->invalidate_bone_cache( );
		}

		auto collideable = object.owner->get_collideable( );

		if ( !collideable )
			continue;

		player_info.mins = collideable->obb_mins( );
		player_info.maxs = collideable->obb_maxs( );

		player_info.rgfl = player->rgfl_coordinate_frame( );

		if ( !player_info.valid && ticks_to_time( g_interfaces.globals->tick_count - player_info.dormant_info.found_tick ) < 3.f ) {
			player->set_abs_origin( old_origin );
			player->invalidate_bone_cache( );
		}
	}

	g_render.setup_state( );

	g_visuals.render( );

	g_render.finish_state( );

	return end_scene_hook.call_original( device );
}
