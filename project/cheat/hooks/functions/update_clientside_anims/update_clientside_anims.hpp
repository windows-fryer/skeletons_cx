
#ifndef SKELETONS_CX_UPDATE_CLIENTSIDE_ANIMS_HPP
#define SKELETONS_CX_UPDATE_CLIENTSIDE_ANIMS_HPP
#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{

	CREATE_HOOK_HELPER( update_clientside_anims_hook, void( __fastcall )( void*, void*, float, float ), void );

	struct update_clientside_anims {
		static void __fastcall update_clientside_anims_detour( void* ecx, void* edx, float angle_y, float angle_x );

		static void init( )
		{
			update_clientside_anims_hook.create( g_signatures[ "55 8B EC 81 EC ? ? ? ? 53 57 8B F9 8B 9F" ], update_clientside_anims_detour,
			                                     "update_clientside_anims_detour" );
		}

		static void shutdown( )
		{
			update_clientside_anims_hook.disable( );
		}
	};

} // namespace hooks

#endif // SKELETONS_CX_UPDATE_CLIENTSIDE_ANIMS_HPP
