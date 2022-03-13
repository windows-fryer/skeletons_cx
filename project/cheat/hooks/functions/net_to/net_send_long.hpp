#ifndef SKELETONS_CX_NET_SEND_LONG_HPP
#define SKELETONS_CX_NET_SEND_LONG_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( net_send_long_hook, int( __cdecl )( void*, int, void*, void*, int, void*, int, int ), int );

	struct net_send_long {
		static int __cdecl net_send_long_detour( void* channel, int socket, void* socket_address, void* buffer, int length, void* to, int to_length,
		                                         int max_routable );

		static void init( )
		{
			net_send_long_hook.create( g_signatures[ "55 8B EC 81 EC ? ? ? ? 8B 0D ? ? ? ? 33 D2 89 55 ? 89 55 ? 89 55 ? 8B 41" ],
			                           net_send_long_detour, "net_send_long_detour" );
		}

		static void shutdown( )
		{
			net_send_long_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_NET_SEND_LONG_HPP
