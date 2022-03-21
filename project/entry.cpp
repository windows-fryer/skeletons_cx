#include "entry.hpp"

//-----------------------------------------------------------------------------
// @PURPOSE : Initializes the cheat.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void entry::init( )
{
	auto thread_handle = create_thread( cheat::init );

	if ( thread_handle )
		close_handle( thread_handle );
}

void entry::shutdown( ) { }

bool win_api dll_main( hinstance module_handle, std::uintptr_t call_reason, void* reserved )
{
	disable_thread_library_calls( module_handle );

	switch ( call_reason ) {
	case DLL_PROCESS_ATTACH: {
		cheat::module_handle = module_handle;
		entry::init( );
	} break;

	case DLL_PROCESS_DETACH: {
		console::log( "unloading\n" );
		modules::shutdown( );
		console::shutdown( );

		g_signatures.shutdown( );
		g_interfaces.shutdown( );
		g_hooks.shutdown( );
	} break;
	}

	return true;
}