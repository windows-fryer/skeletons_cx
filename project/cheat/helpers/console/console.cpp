#include <Windows.h>
#include <iostream>

#include "../assertion/assertion.hpp"
#include "console.hpp"

bool is_console_initialized = false;

void console::impl::initialize( )
{
	/*  */
	{
		if ( is_console_initialized )
			return;
		is_console_initialized = true;
	}

	if ( !AllocConsole( ) ) {
		// todo: assert shit instead.
		return;
	}

	FILE *con_out, *con_in, *con_err;

	freopen_s( &con_out, "CONIN$", "w", stdin );
	freopen_s( &con_in, "CONOUT$", "w", stdout );
	freopen_s( &con_err, "CONERR$", "w", stderr );
}


constexpr void console::impl::log( std::string_view message )
{
	std::cout << message << '\n';
}
