#include "override_view.hpp"

void hooks::override_view::override_view_detour( void* ecx, void* edx, sdk::c_view_setup* view_setup )
{
	[[unlikely]] if ( !view_setup ) return;

	auto view_entity = ( sdk::c_base_entity* )g_interfaces.entity_list->get_client_entity_from_handle( g_globals.local->view_model( ) );

	if ( !view_entity )
		return override_view_hook.call_original( ecx, edx, view_setup );

	// then you can set angles of it and shit

	override_view_hook.call_original( ecx, edx, view_setup );
}