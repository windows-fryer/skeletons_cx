#ifndef WEDNESDAY_WTF_END_SCENE_HPP
#define WEDNESDAY_WTF_END_SCENE_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( end_scene_hook, long( __stdcall )( IDirect3DDevice9* ), long );

	struct end_scene {
		static long __stdcall end_scene_detour( IDirect3DDevice9* device );

		static void init( )
		{
			end_scene_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.device, 42 ), end_scene_detour, "end_scene_detour" );
		}

		static void shutdown( )
		{
			end_scene_hook.disable( );
		}
	};
} // namespace hooks

#endif // WEDNESDAY_WTF_END_SCENE_HPP
