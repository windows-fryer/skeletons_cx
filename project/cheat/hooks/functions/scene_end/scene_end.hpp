#ifndef SKELETONS_CX_SCENE_END_HPP
#define SKELETONS_CX_SCENE_END_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

#include <fstream>

namespace hooks
{
	CREATE_HOOK_HELPER( scene_end_hook, void( __fastcall )( void*, void* ), void );

	struct scene_end {
		static void __fastcall scene_end_detour( void* ecx, void* edx );

		static void init( )
		{
			scene_end_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.render_view, 9 ), scene_end_detour, "scene_end_detour" );
		}

		static void shutdown( )
		{
			scene_end_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_SCENE_END_HPP
