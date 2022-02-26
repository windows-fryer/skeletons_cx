#ifndef SKELETONS_CX_RENDER_VIEW_HPP
#define SKELETONS_CX_RENDER_VIEW_HPP
#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

// 27 or 28

namespace hooks
{
	CREATE_HOOK_HELPER( override_view_hook, void( __fastcall )( void*, void*, int, float, bool ), void );

	struct override_view {
		static void __fastcall override_view_detour( void* ecx, void* edx, int sequence_number );

		static void init( )
		{
			std::uintptr_t* overrideview  = g_vfunc.get_virtual_function_index( g_interfaces.client_mode, 16 );
			std::uintptr_t* overrideview1 = g_vfunc.get_virtual_function_index( g_interfaces.client_mode, 17 );
			std::cout << "random shit to break on\n";
			// render_view_hook.create( render_view_address, render_view_detour, "render_view_detour" );
		}

		static void shutdown( )
		{
			render_view_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_RENDER_VIEW_HPP
