#include "item_post_frame.hpp"

void hooks::item_post_frame::item_post_frame_detour( void* ecx, void* edx )
{
	if ( g_globals.running_post_think )
		return;

	return item_post_frame_hook.call_original( ecx, edx );
}
