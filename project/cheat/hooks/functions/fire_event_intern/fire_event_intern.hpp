#ifndef SKELETONS_CX_FIRE_EVENT_INTERN_HPP
#define SKELETONS_CX_FIRE_EVENT_INTERN_HPP

#include "../../../globals/globals.hpp"
#include "../../../sdk/structs/i_game_event.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( fire_event_intern_hook, bool( __fastcall )( void*, void*, sdk::i_game_event*, bool, bool ), bool );

	struct fire_event_intern {
		static bool __fastcall fire_event_intern_detour( void* ecx, void* edx, sdk::i_game_event* event, bool server_only, bool client_only );

		static void init( )
		{
			fire_event_intern_hook.create( g_signatures[ "55 8B EC 83 EC 34 53 8B 5D 08 57 8B F9 89 7D FC 85 DB" ], fire_event_intern_detour,
			                               "fire_event_intern_detour" );
		}

		static void shutdown( )
		{
			fire_event_intern_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_FIRE_EVENT_INTERN_HPP
