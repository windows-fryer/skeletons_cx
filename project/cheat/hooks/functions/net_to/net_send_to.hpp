

#ifndef SKELETONS_CX_NET_SEND_TO_HPP
#define SKELETONS_CX_NET_SEND_TO_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( net_send_to_hook, int( __cdecl )( bool, SOCKET, void*, int, void*, int, int ), int );

	struct net_send_to {
		static int __cdecl net_send_to_detour( bool verbose, SOCKET s, void* buf, int len, void* to, int tolen, int iGameDataLength );

		static void init( )
		{
			net_send_to_hook.create( g_signatures[ "55 8B EC 83 EC ? 53 56 8B 35 ? ? ? ? 33 DB 57 33 FF 89 5D ? 89 7D ? 8B 46" ], net_send_to_detour,
			                         "net_send_to_detour" );
		}

		static void shutdown( )
		{
			net_send_to_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_NET_SEND_TO_HPP
