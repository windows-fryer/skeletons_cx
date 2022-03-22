#ifndef WEDNESDAY_WTF_WNDPROC_HPP
#define WEDNESDAY_WTF_WNDPROC_HPP

#include "../../../globals/globals.hpp"
#include "../../../sdk/structs/c_view_setup.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	inline WNDPROC wndproc_hook;

	struct wndproc {
		static long win_api wndproc_detour( HWND window, unsigned int message, WPARAM parameter, LPARAM long_parameter );

		static void init( )
		{
			wndproc_hook = reinterpret_cast< WNDPROC >(
				set_window_long( find_window( "Valve001", nullptr ), GWL_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_detour ) ) );
		}

		static void shutdown( )
		{
			set_window_long( find_window( "Valve001", nullptr ), GWL_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_hook ) );
		}
	};
} // namespace hooks

#endif // WEDNESDAY_WTF_WNDPROC_HPP
