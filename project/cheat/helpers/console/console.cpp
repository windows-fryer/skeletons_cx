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

void console::color::blue( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}

void console::color::red( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_INTENSITY );
}

void console::color::green( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}

void console::color::yellow( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
}

void console::color::white( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}

void console::color::cyan( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_BLUE );
}

void console::color::purple( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_BLUE );
}

void console::color::grey( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_INTENSITY );
}