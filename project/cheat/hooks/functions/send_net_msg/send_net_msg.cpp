#include "send_net_msg.hpp"
#include <algorithm>

bool hooks::send_net_msg::send_net_msg_detour( void* ecx, void* edx, sdk::i_net_message& message, bool unk1, bool unk2 )
{
	if ( _ReturnAddress( ) == g_signatures[ "8B 45 ? C7 45 ? ? ? ? ? 5F 5E 85 C0 74 ? 6A ? 50 E8 ? ? ? ? 83 C4 ? 8B E5 5D C3" ] ) {
		auto extra_commands = g_signatures[ "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? DD 1D" ].add( 0x2 ).get( 2 ).as< int >( );

		if ( extra_commands - std::clamp( extra_commands, 0, 16 ) > 0 )
			reinterpret_cast< sdk::i_net_channel* >( ecx )->get_choked_packets( ) -=
				extra_commands - std::clamp( extra_commands, 0, 16 ); // tf2 moment lol
	}

	return send_net_msg_hook.call_original( ecx, edx, message, unk1, unk2 );
}
