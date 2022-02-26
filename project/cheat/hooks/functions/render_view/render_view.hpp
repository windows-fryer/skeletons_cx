#ifndef SKELETONS_CX_RENDER_VIEW_HPP
#define SKELETONS_CX_RENDER_VIEW_HPP
#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( override_view_hook, void( __fastcall )( void*, void*, int, float, bool ), void );

	struct override_view {
		static void __fastcall override_view_detour( void* ecx, void* edx, int sequence_number );

		static void init( )
		{
			std::uintptr_t* overrideview = g_vfunc.get_virtual_function_index( g_interfaces.client_mode, 16 );
		}

		static void shutdown( )
		{
			override_view_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_RENDER_VIEW_HPP
