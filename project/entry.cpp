#include "entry.hpp"

void entry::init( )
{
	/* initialize console here since we wanna output to it whilst initializing */
	console::init( );
	// console::log( "console initialized, creating thread\n" );

	/* setup thread */
	{
		auto thread_handle = create_thread( cheat::init );

		if ( thread_handle ) // todo: assertion
			close_handle( thread_handle );
	}
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