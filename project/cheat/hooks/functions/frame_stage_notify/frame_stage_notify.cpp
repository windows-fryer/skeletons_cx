#include "frame_stage_notify.hpp"
#include "../../../features/aimbot/aimbot.hpp"
#include <algorithm>

void __fastcall hooks::frame_stage_notify::frame_stage_notify_detour( void* ecx, void* edx, sdk::client_frame_stage stage )
{
	frame_stage_notify_hook.call_original( ecx, edx, stage );

	switch ( stage ) {
	case sdk::client_frame_stage::frame_net_update_end: {
		g_entity_list.update( );
		g_lagcomp.update( );

		if ( g_globals.local )
			g_globals.local->force_taunt_cam( ) = g_config.find< bool >( fnv( "third_person" ) );

		for ( auto& player_info : g_entity_list.players ) {
			if ( player_info.valid ) {
				if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
					if ( auto var_map = entity->get_var_mapping( ) ) {
						for ( int iterator = 0; iterator < var_map->interpolated_entries; iterator++ ) {
							var_map->entries[ iterator ].needs_to_interpolate = false;
						}
					}
				}
			}
		}
	} break;
	case sdk::client_frame_stage::frame_render_start: {
		/* re-extrapolate ents */
		{
			// for ( auto& player_info : g_entity_list.players ) {
			//	if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
			//  we do tick math because its easier for me to visualize

			//		auto origin                = entity->origin( ); // dont touch actual origin as we need it for reference
			//		float simulationtime_delta = entity->simulation_time( ) - entity->get_old_simulation_time( ); // delta / choked

			//		auto velocity_per_tick = entity->velocity( ) * g_interfaces.globals->interval_per_tick;

			/* get velocity player wouldve traveled in those choked ticks */
			//		sdk::vector extrapolate_origin = origin + ( velocity_per_tick * time_to_ticks( simulationtime_delta ) );

			//		entity->set_abs_origin( extrapolate_origin );
			//	}
			//}
		}
	} break;
	}
}