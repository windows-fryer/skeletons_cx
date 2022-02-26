#include "cheat.hpp"

void cheat::init( )
{
	modules::init( );
	console::init( );

	g_signatures.init( );
	g_interfaces.init( );
	g_hooks.init( );
}

void cheat::shutdown( )
{
	modules::shutdown( );
	console::shutdown( );

	g_signatures.shutdown( );
	g_interfaces.shutdown( );
	g_hooks.shutdown( );
}