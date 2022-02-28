#include "lagcomp.hpp"
#include "../../globals/globals.hpp"
#include <algorithm>

bool lagcomp::impl::is_valid( record heap_record )
{
	// sanity check
	auto nci = g_interfaces.engine_client->get_net_channel_info( );

	if ( !nci )
		return false;

	float correct = 0.f;

	static auto unlag_pointer = g_interfaces.cvar->find_var( "sv_maxunlag" );
	auto sv_maxunlag          = unlag_pointer->get_float( );

	correct += nci->get_latency( 0 );
	correct += lerp_time( );

	correct = std::clamp( correct, 0.f, sv_maxunlag );

	float delta_correct = std::fabsf( correct - ( g_interfaces.globals->cur_time - heap_record.simulation_time ) );

	return delta_correct <= .2f;
}

float lagcomp::impl::lerp_time( )
{
	static sdk::con_var *cl_updaterate   = g_interfaces.cvar->find_var( "cl_updaterate" ),
						*cl_interp_ratio = g_interfaces.cvar->find_var( "cl_interp_ratio" ), *cl_interp = g_interfaces.cvar->find_var( "cl_interp" ),
						*sv_client_min_interp_ratio = g_interfaces.cvar->find_var( "sv_client_min_interp_ratio" ),
						*sv_client_max_interp_ratio = g_interfaces.cvar->find_var( "sv_client_max_interp_ratio" );

	static auto interp_ratio = std::max( cl_interp_ratio->get_float( ), 1.f );

	interp_ratio = std::clamp( interp_ratio, sv_client_min_interp_ratio->get_float( ), sv_client_max_interp_ratio->get_float( ) );

	return std::max( cl_interp->get_float( ), interp_ratio / cl_updaterate->get_int( ) );
}

void lagcomp::impl::update( )
{
	static auto unlag_pointer = g_interfaces.cvar->find_var( "sv_maxunlag" );
	auto sv_maxunlag          = unlag_pointer->get_float( );
	auto sv_maxunlag_ticks    = time_to_ticks( sv_maxunlag );

	for ( auto& player_info : g_entity_list.players ) {
		auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index );

		if ( !player_info.valid || !player ) {
			if ( heap_records[ player_info.index ] ) {
				delete[] heap_records[ player_info.index ];
				heap_records[ player_info.index ] = NULL;
			}

			continue;
		}

		auto& current_heap_iterator = heap_iterator[ player->entindex( ) ];

		if ( !heap_records[ player_info.index ] )
			heap_records[ player_info.index ] = new record[ sv_maxunlag_ticks ];

		for ( int current_heap_iterator = 0; current_heap_iterator < sv_maxunlag_ticks; current_heap_iterator++ ) {
			auto current_record = &g_lagcomp.heap_records[ player->entindex( ) ][ current_heap_iterator ];

			if ( !current_record )
				continue;

			current_record->valid = is_valid( *current_record );
		}

		auto& current_record = heap_records[ player_info.index ][ current_heap_iterator ];

		current_record.abs_origin      = player->get_abs_origin( );
		current_record.eye_position    = player->eye_position( );
		current_record.simulation_time = player->simulation_time( );
		current_record.valid           = is_valid( current_record );
		current_record.player          = player;
		player->setup_bones( current_record.bone_matrix, 128, 256, 0.f );

		current_heap_iterator++;

		if ( current_heap_iterator >= sv_maxunlag_ticks )
			current_heap_iterator = 0;
	}
}

void lagcomp::impl::backtrack_player( record* heap_record )
{
	g_globals.lagcomp_record = heap_record;

	if ( !heap_record )
		return;

	g_globals.command->tick_count = time_to_ticks( heap_record->simulation_time + lerp_time( ) );
}

void lagcomp::impl::backtrack_player( sdk::c_tf_player* player )
{
	static auto unlag_pointer = g_interfaces.cvar->find_var( "sv_maxunlag" );
	auto sv_maxunlag_ticks    = time_to_ticks( unlag_pointer->get_float( ) );

	auto entity_index = player->entindex( );

	auto closest_fov = FLT_MAX;
	record* closest_record{ };

	sdk::qangle player_angles;
	g_interfaces.engine_client->get_view_angles( player_angles );

	if ( !heap_records[ entity_index ] )
		return;

	for ( int current_heap_iterator = 0; current_heap_iterator < sv_maxunlag_ticks; current_heap_iterator++ ) {
		auto current_record = &heap_records[ entity_index ][ current_heap_iterator ];

		if ( !current_record )
			continue;

		if ( !current_record->valid )
			continue;

		auto record_fov = math::get_fov( player_angles, g_globals.local->eye_position( ), current_record->eye_position );

		if ( record_fov < closest_fov ) {
			closest_fov    = record_fov;
			closest_record = current_record;
		}
	}

	g_globals.lagcomp_record = closest_record;

	if ( !closest_record )
		return;

	// https://github.com/perilouswithadollarsign/cstrike15_src/blob/master/game/server/player_lagcompensation.cpp#L287
	// ty dalkr :3

	g_globals.command->tick_count = time_to_ticks( closest_record->simulation_time + lerp_time( ) );
}
