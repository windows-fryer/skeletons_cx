#include "entry.hpp"

void entry::init( )
{
	create_thread( cheat::init );
}

void entry::shutdown( )
{

}

bool win_api dll_main( HINSTANCE module_handle, std::uintptr_t reason, void* reserved )
{
	switch ( reason ) {
	case DLL_PROCESS_ATTACH:
		entry::init( );
		break;
	}

	return true;
}