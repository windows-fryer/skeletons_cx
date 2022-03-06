#include "override_view.hpp"

void hooks::override_view::override_view_detour( void* ecx, void* edx, sdk::c_view_setup* view_setup )
{
	[[unlikely]] if ( !view_setup ) return;

	// Wow! a liga comment? unexpected. liga never comments due to the fact he cant code and doesnt know what hes actually doing
	// Keep this here so we can forever remember how much of a fucking idiot blanket it
	if ( !g_globals.local )
		return override_view_hook.call_original( ecx, edx, view_setup );

	auto view_entity = g_interfaces.entity_list->get< sdk::c_base_entity >( g_globals.local->view_model( ) );

	if ( !view_entity )
		return override_view_hook.call_original( ecx, edx, view_setup );
	
	// then you can set angles of it and shit

	override_view_hook.call_original( ecx, edx, view_setup );
}