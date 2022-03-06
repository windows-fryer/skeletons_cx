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

	/* third person here for now */
	{
		if ( g_globals.local->is_alive( ) ) {
			sdk::qangle view_angles;
			g_interfaces.engine_client->get_view_angles( view_angles );

			sdk::vector forward{ }, right{ }, up{ };
			math::angle_to_vector( view_angles, &forward, &right, &up );

			/* get the third person distance */
			sdk::vector new_origin = view_setup->origin - ( forward * 200 );

			/* do ray trace to ensure we dont see through walls lel */
			sdk::c_game_trace trace;
			sdk::c_trace_filter_world_and_props_only filter;
			sdk::ray_t ray;
			ray.init( view_setup->origin, new_origin );

			/* no def for mask_shot yet, too lazy */
			g_interfaces.engine_trace->trace_ray( ray, ( 0x1 | 0x4000 | 0x10000 | 0x2 | 0x4000000 | 0x40000000 ), &filter, &trace );

			/* if fraction is 1.f then we didnt hit shit and can have far third person */
			if ( trace.fraction == 1.f ) {
				view_setup->origin = new_origin;
			} else {
				/* else we set our distance to where the ray hit ass a lil to prevent clipping issues */
				view_setup->origin = trace.endpos;
			}
		}
	}

	// then you can set angles of it and shit

	override_view_hook.call_original( ecx, edx, view_setup );
}