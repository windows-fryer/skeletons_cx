#include "entry.hpp"

void entry::init( )
{
	if ( auto handle = create_thread( cheat::init ) )
		close_handle( handle );
}

void entry::shutdown( ) { }

bool win_api dll_main( HINSTANCE module_handle, std::uintptr_t reason, void* reserved )
{
	switch ( reason ) {
	case DLL_PROCESS_ATTACH:
		cheat::module_handle = module_handle;

		entry::init( );

		break;
	}

	return true;
}