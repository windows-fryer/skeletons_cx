#include "render_view.hpp"

void hooks::override_view::override_view_detour( void* ecx, void* edx, void* view_setup )
{
	override_view_hook.call_original( ecx, edx, view_setup );
}