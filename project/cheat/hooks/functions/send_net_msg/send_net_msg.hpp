#ifndef SKELETONS_CX_SEND_NET_MSG_HPP
#define SKELETONS_CX_SEND_NET_MSG_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( send_net_msg_hook, bool( __fastcall )( void*, void*, sdk::i_net_message&, bool, bool ), bool );

	struct send_net_msg {
		static bool __fastcall send_net_msg_detour( void* ecx, void* edx, sdk::i_net_message& message, bool unk1, bool unk2 );

		static void init( )
		{
			send_net_msg_hook.create( g_signatures[ "55 8B EC 56 8B F1 8D 8E ? ? ? ? E8 ? ? ? ? 85 C0 75" ], send_net_msg_detour,
			                          "send_net_msg_detour" );
		}

		static void shutdown( )
		{
			send_net_msg_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_SEND_NET_MSG_HPP
