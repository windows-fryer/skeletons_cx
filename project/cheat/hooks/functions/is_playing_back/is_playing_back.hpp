#ifndef SKELETONS_CX_IS_PLAYING_BACK_HPP
#define SKELETONS_CX_IS_PLAYING_BACK_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( is_playing_back_hook, bool( __fastcall )( void*, void* ), bool );

	struct is_playing_back {
		static bool __fastcall is_playing_back_detour( void* ecx, void* edx );

		static void init( )
		{
			is_playing_back_hook.create( g_signatures[ "8A 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 80 B9" ], is_playing_back_detour,
			                             "is_playing_back_detour" );
		}

		static void shutdown( )
		{
			is_playing_back_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_IS_PLAYING_BACK_HPP
