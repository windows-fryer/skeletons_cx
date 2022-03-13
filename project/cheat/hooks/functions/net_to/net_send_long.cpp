#include "net_send_long.hpp"

int hooks::net_send_long::net_send_long_detour( void* channel, int socket, void* socket_address, void* buffer, int length, void* to, int to_length,
                                                int max_routable )
{
	int result = net_send_long_hook.call_original( channel, socket, socket_address, buffer, length, to, to_length, max_routable );

	return result;
}
