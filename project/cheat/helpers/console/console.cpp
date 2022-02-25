#include <Windows.h>

#include "../assertion/assertion.hpp"
#include "console.hpp"

void console::init( )
{
	if ( !AllocConsole( ) ) {
		// todo: assert shit instead.
		return;
	}

	FILE *con_out, *con_in, *con_err;

	freopen_s( &con_out, "CONIN$", "w", stdin );
	freopen_s( &con_in, "CONOUT$", "w", stdout );
	freopen_s( &con_err, "CONERR$", "w", stderr );
}

void console::shutdown( )
{
	FreeConsole();
}
