#include "override_view.hpp"

void hooks::override_view::override_view_detour( void* ecx, void* edx, sdk::c_view_setup* view_setup )
{
	[[unlikely]] if ( !view_setup ) return;

	view_setup->fov = 100;

	override_view_hook.call_original( ecx, edx, view_setup );
}