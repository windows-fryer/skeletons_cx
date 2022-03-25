#ifndef WEDNESDAY_WTF_SNAKEIFY_HPP
#define WEDNESDAY_WTF_SNAKEIFY_HPP

#include "../../dependencies/fnv/fnv.hpp"

#define hinstance HINSTANCE

#define dll_main                         DllMain
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
#define disable_thread_library_calls     DisableThreadLibraryCalls
#define win_api                          WINAPI

#define time_to_ticks( time )       static_cast< std::int32_t >( time / g_interfaces.globals->interval_per_tick )
#define ticks_to_time( ticks )      static_cast< float >( ticks ) * g_interfaces.globals->interval_per_tick
#define time_to_ticks_round( time ) static_cast< std::int32_t >( ( time / g_interfaces.globals->interval_per_tick ) + 0.5f )

#define ROUND_UP( value ) static_cast< int >( static_cast< float >( value ) + 0.5f )
#define DEVICE_SAFETY( )                                                                                                                             \
	if ( !render::device ) {                                                                                                                         \
		return;                                                                                                                                      \
	}

#define FAIL_CHECK( return_code )                                                                                                                    \
	if ( FAILED( return_code ) )                                                                                                                     \
		return;

#define COMBINE( lhs, rhs ) lhs##rhs
#define CONCAT( lhs, rhs )  COMBINE( lhs, rhs )
#define PAD( size )                                                                                                                                  \
private:                                                                                                                                             \
	std::uint8_t CONCAT( pad, __COUNTER__ )[ size ];                                                                                                 \
                                                                                                                                                     \
public:

#endif // WEDNESDAY_WTF_SNAKEIFY_HPP
