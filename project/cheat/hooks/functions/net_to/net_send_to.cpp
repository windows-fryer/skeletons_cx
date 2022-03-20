#include "net_send_to.hpp"

int __cdecl hooks::net_send_to::net_send_to_detour( bool verbose, SOCKET s, void* buf, int len, const struct sockaddr* to, int tolen,
                                                    int game_data_len )
{
	return hooks::net_send_to_hook.call_original( verbose, s, buf, len, to, tolen, game_data_len );
}