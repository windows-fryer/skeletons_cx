#ifndef SKELETONS_CX_SNAKEIFY_HPP
#define SKELETONS_CX_SNAKEIFY_HPP

#include "../../dependencies/fnv/fnv.hpp"

#define dll_main                         DllMain
#define win_api                          WINAPI
#define create_thread( function )        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )
#define fnv( string )                    fnv::hash( string )
#define get_proc_address( module, name ) GetProcAddress( module, name )
#define get_module_handle( name )        GetModuleHandle( name )
#define set_window_long                  SetWindowLongA
#define find_window                      FindWindowA
#define call_window_proc                 CallWindowProcA
#define free_library_and_exit_thread     FreeLibraryAndExitThread
#define close_handle                     CloseHandle
#define free_console                     FreeConsole

#define ROUND_UP( value ) static_cast< int >( static_cast< float >( value ) + 0.5f )
#define DEVICE_SAFETY( )                                                                                                                             \
	if ( !render::device ) {                                                                                                                         \
		return;                                                                                                                                      \
	}

#define FAIL_CHECK( return_code )                                                                                                                    \
	if ( FAILED( return_code ) )                                                                                                                     \
		return;

#endif // SKELETONS_CX_SNAKEIFY_HPP
