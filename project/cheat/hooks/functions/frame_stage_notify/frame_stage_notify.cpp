#include "frame_stage_notify.hpp"

void __fastcall hooks::frame_stage_notify::frame_stage_notify_detour( void* ecx, void* edx, sdk::client_frame_stage stage )
{
	switch ( stage ) {
	case sdk::client_frame_stage::frame_net_update_end: {
		g_entity_list.update( );
		g_lagcomp.update( );

		for ( auto& entity : g_entity_list.players ) {
			// if ( auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( entity.index ) ) {
			//	if ( auto var_map = player->get_var_mapping( ) ) {
			//		for ( int iterator = 0; iterator < var_map->interpolated_entries; iterator++ ) {
			//	var_map->entries[ iterator ].needs_to_interpolate = false;
			//		}
			//	}
			//}
		}
	} break;
	}

	frame_stage_notify_hook.call_original( ecx, edx, stage );
}