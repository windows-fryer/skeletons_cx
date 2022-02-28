#include "net_send_to.hpp"

int __cdecl hooks::net_send_to::net_send_to_detour( bool verbose, SOCKET s, void* buf, int len, void* to, int tolen, int data_len )
{
	int result = hooks::net_send_to_hook.call_original( verbose, s, buf, len, to, tolen, data_len );

#if 0
	if ( GetAsyncKeyState( VK_XBUTTON2 ) ) {
		char* allocated_nigga = ( char* )malloc( 120 );
		for ( int i = 0; i < 100; i++ )
			hooks::net_send_to_hook.call_original( verbose, s, allocated_nigga, len, to, tolen, data_len );
		free( allocated_nigga );
	}
#endif

	return result;
}