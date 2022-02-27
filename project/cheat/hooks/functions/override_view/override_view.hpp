#ifndef SKELETONS_CX_OVERRIDE_VIEW_HPP
#define SKELETONS_CX_OVERRIDE_VIEW_HPP
#include "../../../globals/globals.hpp"
#include "../../../sdk/structs/c_view_setup.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	// this isnt right (probably) however cviewsetup is always the only thing pushed on to stack so we dont care about other args
	CREATE_HOOK_HELPER( override_view_hook, void( __fastcall )( void*, void*, sdk::c_view_setup* ), void );

	struct override_view {
		static void __fastcall override_view_detour( void* ecx, void* edx, sdk::c_view_setup* view_setup );

		static void init( )
		{
			override_view_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.client_mode, 16 ), override_view_detour,
			                           "override_view_detour" );
		}

		static void shutdown( )
		{
			override_view_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_OVERRIDE_VIEW_HPP
