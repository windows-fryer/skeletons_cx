#ifndef WEDNESDAY_WTF_GET_TIME_HPP
#define WEDNESDAY_WTF_GET_TIME_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( get_time_hook, float( __fastcall )( void*, void* ), float );

	struct get_time {
		static float __fastcall get_time_detour( void* ecx, void* edx );

		static void init( )
		{
			get_time_hook.create( g_signatures[ "55 8B EC 51 80 B9 14 4B 00 00" ], get_time_detour, "get_time_detour" );
		}

		static void shutdown( )
		{
			get_time_hook.disable( );
		}
	};
} // namespace hooks

#endif // WEDNESDAY_WTF_GET_TIME_HPP
