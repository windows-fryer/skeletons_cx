#include "entry.hpp"

void entry::impl::init( )
{
	create_thread( g_cheat.init );
}

void entry::impl::shutdown( )
{

}

bool win_api dll_main( HINSTANCE module_handle, std::uintptr_t reason, void* reserved )
{
	switch ( reason ) {
	case DLL_PROCESS_ATTACH:
		entry::impl::init( );
		break;
	case DLL_PROCESS_DETACH:
		entry::impl::shutdown( );
		break;
	}

	return true;
}