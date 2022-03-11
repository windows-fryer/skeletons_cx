#include "item_post_frame.hpp"

void hooks::item_post_frame::item_post_frame_detour( void* ecx, void* edx )
{
	if ( _ReturnAddress( ) == g_signatures[ "F6 87 ? ? ? ? ? 74 ? C7 87 ? ? ? ? ? ? ? ? 83 BF" ] && g_globals.running_post_think )
		return;

	return item_post_frame_hook.call_original( ecx, edx );
}
