#include "cheat.hpp"

void cheat::init( )
{
	modules::init();
	g_interfaces.init( );
}

void cheat::shutdown( )
{
	g_interfaces.shutdown( );
}