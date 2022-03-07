#ifndef SKELETONS_CX_ENUMERATE_LEAVES_IN_BOX_HPP
#define SKELETONS_CX_ENUMERATE_LEAVES_IN_BOX_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( enumerate_leaves_in_box_hook, bool( __fastcall )( void*, void*, sdk::vector&, sdk::vector&, void*, int ), bool );

	struct enumerate_leaves_in_box {
		static bool __fastcall enumerate_leaves_in_box_detour( void* ecx, void* edx, sdk::vector& mins, sdk::vector& maxs, void* enumerator,
		                                                       int context );

		static void init( )
		{
			enumerate_leaves_in_box_hook.create( g_signatures[ "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 83 EC ? 83 3D" ],
			                                     enumerate_leaves_in_box_detour, "enumerate_leaves_in_box_detour" );
		}

		static void shutdown( )
		{
			enumerate_leaves_in_box_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_ENUMERATE_LEAVES_IN_BOX_HPP
