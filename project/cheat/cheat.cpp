#include "cheat.hpp"

void cheat::init( )
{
	modules::init( );

	g_signatures.init( );
	g_interfaces.init( );
	g_hooks.init( );
	g_render.init( g_interfaces.device );
	g_menu.init( );

	g_input.add_keybind( VK_DELETE, []( bool down ) {
		if ( auto handle = create_thread( shutdown ) )
			close_handle( handle );
	} );
}

void cheat::shutdown( )
{
	free_library_and_exit_thread( cheat::module_handle, 0 );
}