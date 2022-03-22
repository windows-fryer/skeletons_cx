#ifndef WEDNESDAY_WTF_CL_MOVE_HPP
#define WEDNESDAY_WTF_CL_MOVE_HPP

#include "../../../globals/globals.hpp"
#include "../../../sdk/structs/c_view_setup.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( cl_move_hook, void( __cdecl )( float, bool ), void );

	struct cl_move {
	private:
		static void clear_ticks( float accumulated_extra_samples, bool final_tick );
		static void store_tick( );
		static void shift_ticks( float accumulated_extra_samples, bool final_tick );

	public:
		static void __cdecl cl_move_detour( float accumulated_extra_samples, bool final_tick );

		static void init( )
		{
			g_input.add_keybind( 'e', []( bool down ) {
				if ( down )
					g_globals.force_shift = true;
				else
					g_globals.force_shift = false;
			} );
			g_input.add_keybind( 'r', []( bool down ) {
				if ( down )
					g_globals.force_charge = true;
				else
					g_globals.force_charge = false;
			} );

			cl_move_hook.create( g_signatures[ "55 8B EC 83 EC 38 83 3D ? ? ? ? ?" ], cl_move_detour, "cl_move_detour" );
		}

		static void shutdown( )
		{
			cl_move_hook.disable( );
		}
	};
} // namespace hooks
#endif // WEDNESDAY_WTF_CL_MOVE_HPP
