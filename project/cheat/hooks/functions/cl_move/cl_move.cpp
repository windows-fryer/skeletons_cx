#include "cl_move.hpp"

void hooks::cl_move::cl_move_detour( float accumulated_extra_samples, bool final_tick )
{
	if ( !g_interfaces.engine_client->is_in_game( ) )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_globals.local )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_config.find< bool >( fnv( "double_tap" ) ) )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_globals.command )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( g_globals.stored_ticks < 24 && !( g_globals.command->buttons & sdk::in_attack ) )
		return store_tick( );

	g_globals.charging = false;

	cl_move_hook.call_original( accumulated_extra_samples, final_tick );

	// Not sure if final tick is needed but whatever, makes it more accurate fo da culture!!
	if ( g_globals.command->buttons & sdk::in_attack )
		return shift_ticks( accumulated_extra_samples, final_tick );
}

void hooks::cl_move::clear_ticks( float accumulated_extra_samples, bool final_tick )
{
	cl_move_hook.call_original( accumulated_extra_samples, final_tick );

	if ( !g_interfaces.net_channel )
		return;

	auto shiftable_ticks = g_globals.stored_ticks - g_interfaces.net_channel->get_choked_packets( );

	if ( shiftable_ticks < 1 )
		return;

	g_globals.shifting = true;

	for ( int tick = 0; tick < shiftable_ticks; tick++ ) {
		if ( tick != shiftable_ticks - 1 )
			g_globals.choke = true;
		else
			g_globals.choke = false;

		g_globals.stored_ticks--;

		cl_move_hook.call_original( accumulated_extra_samples, final_tick );
	}

	g_globals.stored_ticks = 0;
	g_globals.shifting     = false;
	g_globals.choke        = false;
	g_globals.last_tick    = 0;
}

void hooks::cl_move::store_tick( )
{
	g_globals.charging = true;
	g_globals.stored_ticks++;
	g_globals.last_tick = g_interfaces.globals->tick_count;
}

void hooks::cl_move::shift_ticks( float accumulated_extra_samples, bool final_tick )
{
	if ( !g_interfaces.net_channel )
		return;

	// Source engine supa powerfow
	auto shiftable_ticks = g_globals.stored_ticks - g_interfaces.net_channel->get_choked_packets( );

	if ( shiftable_ticks < 1 )
		return;

	g_globals.shifting = true;

	for ( int tick = 0; tick < shiftable_ticks; tick++ ) {
		if ( tick != shiftable_ticks - 1 )
			g_globals.choke = true;
		else
			g_globals.choke = false;

		g_globals.stored_ticks--;

		cl_move_hook.call_original( accumulated_extra_samples, final_tick );
	}

	g_globals.choke    = false;
	g_globals.shifting = false;
}
