#include "cheat.hpp"

void cheat::init( )
{
	modules::init( );
	console::init( );

	g_signatures.init( );
	g_interfaces.init( );
	g_hooks.init( );
	g_render.init( g_interfaces.device );
	g_menu.init();

	g_input.add_keybind( VK_DELETE, []( bool down ) {
		if ( auto handle = create_thread( shutdown ) )
			close_handle( handle );
	} );
}

void cheat::shutdown( )
{
	modules::shutdown( );
	console::shutdown( );

	g_signatures.shutdown( );
	g_interfaces.shutdown( );
	g_hooks.shutdown( );

	free_library_and_exit_thread( cheat::module_handle, EXIT_SUCCESS );
}