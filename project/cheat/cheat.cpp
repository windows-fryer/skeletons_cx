#include "cheat.hpp"

void cheat::init( )
{
	modules::init( );
	console::init( );

	g_interfaces.init( );
}

void cheat::shutdown( )
{
	g_interfaces.shutdown( );
}