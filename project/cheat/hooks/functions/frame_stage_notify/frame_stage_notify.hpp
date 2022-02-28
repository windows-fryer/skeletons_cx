#ifndef SKELETONS_CX_FRAME_STAGE_NOTIFY_HPP
#define SKELETONS_CX_FRAME_STAGE_NOTIFY_HPP

#include "../../../features/lagcomp/lagcomp.hpp"
#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( frame_stage_notify_hook, void( __fastcall )( void*, void*, sdk::client_frame_stage ), void );

	struct frame_stage_notify {
		static void __fastcall frame_stage_notify_detour( void* ecx, void* edx, sdk::client_frame_stage stage );

		static void init( )
		{
			frame_stage_notify_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.base_client, 35 ), frame_stage_notify_detour,
			                                "frame_stage_notify_detour" );
		}

		static void shutdown( )
		{
			frame_stage_notify_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_FRAME_STAGE_NOTIFY_HPP
