#include "cheat.hpp"
#include "helpers/assertion/assertion.hpp"

//-----------------------------------------------------------------------------
// @PURPOSE : Starts up every module inside the cheat.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void cheat::init( )
{
	console::init( );
	assert_block( "modules", modules::init( ) );

	assert_block( "signatures", g_signatures.init( ) );
	assert_block( "interfaces", g_interfaces.init( ) );
	assert_block( "render", g_render.init( g_interfaces.device ) );
	assert_block( "menu", g_menu.init( ) );
	assert_block( "hooks", g_hooks.init( ) );

	g_input.add_keybind( VK_DELETE, []( bool down ) {
		if ( auto handle = create_thread( shutdown ) )
			close_handle( handle );
	} );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Used for unloading the cheat.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void cheat::shutdown( )
{
	free_library_and_exit_thread( cheat::module_handle, 0 );
}