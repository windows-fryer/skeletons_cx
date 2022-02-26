#ifndef SKELETONS_CX_CREATE_MOVE_HPP
#define SKELETONS_CX_CREATE_MOVE_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( create_move_hook, void( __fastcall )( void*, void*, int, float, bool ), void );

	struct create_move {
		static void __fastcall create_move_detour( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active );

		static void init( )
		{
			create_move_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.base_client, 21 ), create_move_detour, "create_move_detour" );
		}

		static void shutdown( )
		{
			create_move_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_CREATE_MOVE_HPP
