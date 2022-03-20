#ifndef SKELETONS_CX_NET_SEND_PACKET_HPP
#define SKELETONS_CX_NET_SEND_PACKET_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( net_send_packet_hook, int( __cdecl )( sdk::i_net_channel*, int, void*, unsigned char*, int, sdk::bf_write*, bool ), int );

	struct net_send_packet {
		static int __cdecl net_send_packet_detour( sdk::i_net_channel* channel, int socket, void* to, unsigned char* data, int length,
		                                           sdk::bf_write* voice_payload, bool use_compression );

		static void init( )
		{
			net_send_packet_hook.create( g_signatures[ "55 8B EC B8 88 20 00 00" ], net_send_packet_detour, "net_send_packet_detour" );
		}

		static void shutdown( )
		{
			net_send_packet_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_NET_SEND_PACKET_HPP
