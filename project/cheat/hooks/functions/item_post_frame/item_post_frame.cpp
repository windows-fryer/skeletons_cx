#include "item_post_frame.hpp"

void hooks::item_post_frame::item_post_frame_detour( void* ecx, void* edx )
{
	if ( g_globals.running_post_think )
		return;

	sdk::vector old_viewpunch{ };

	//	if ( g_globals.local ) {
	//		old_viewpunch                   = g_globals.local->punch_angle( );
	//		g_globals.local->punch_angle( ) = { 0, 100, 0 };
	//	}

	item_post_frame_hook.call_original( ecx, edx );
}
