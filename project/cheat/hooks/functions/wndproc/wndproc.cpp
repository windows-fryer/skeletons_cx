#include "wndproc.hpp"

long win_api hooks::wndproc::wndproc_detour( HWND window, unsigned int message, WPARAM parameter, LPARAM long_parameter )
{
	g_input.think( message, parameter, long_parameter );

	return call_window_proc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
