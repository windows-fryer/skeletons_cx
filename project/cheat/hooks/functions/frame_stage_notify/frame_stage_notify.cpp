#include "frame_stage_notify.hpp"

void __fastcall hooks::frame_stage_notify::frame_stage_notify_detour( void* ecx, void* edx, sdk::client_frame_stage stage )
{
	switch ( stage ) {
	case sdk::client_frame_stage::frame_net_update_end:
		g_entity_list.update( );
	}

	frame_stage_notify_hook.call_original( ecx, edx, stage );
}