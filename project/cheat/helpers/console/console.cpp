#include <Windows.h>

#include "../../globals/snakeify.hpp"
#include "../assertion/assertion.hpp"
#include "console.hpp"

void console::init( )
{
	if ( !AllocConsole( ) ) {
		// todo: assert shit instead.
		return;
	}

	freopen_s( &con_out, "CONIN$", "w", stdin );
	freopen_s( &con_in, "CONOUT$", "w", stdout );
}

void console::shutdown( )
{
	fclose( con_out );
	fclose( con_in );

	free_console( );
}
