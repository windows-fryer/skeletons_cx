#include "cl_move.hpp"

void hooks::cl_move::cl_move_detour( float accumulated_extra_samples, bool final_tick )
{
	if ( !g_interfaces.engine_client->is_in_game( ) )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_globals.local )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_globals.local->is_alive( ) )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( !g_globals.command )
		return clear_ticks( accumulated_extra_samples, final_tick );

	if ( g_globals.stored_ticks < 24 && !( g_globals.command->buttons & sdk::in_attack ) )
		return store_tick( );

	cl_move_hook.call_original( accumulated_extra_samples, final_tick );

	// Not sure if final tick is needed but whatever, makes it more accurate fo da culture!!
	if ( g_globals.command->buttons & sdk::in_attack && final_tick )
		return shift_ticks( accumulated_extra_samples, final_tick );
}

void hooks::cl_move::clear_ticks( float accumulated_extra_samples, bool final_tick )
{
	g_globals.stored_ticks = 0;
	g_globals.shifting     = false;
	g_globals.choke        = false;

	cl_move_hook.call_original( accumulated_extra_samples, final_tick );
}

void hooks::cl_move::store_tick( )
{
	g_globals.stored_ticks++;
}

void hooks::cl_move::shift_ticks( float accumulated_extra_samples, bool final_tick )
{
	auto net_channel = reinterpret_cast< sdk::i_net_channel* >( g_interfaces.engine_client->get_net_channel_info( ) );

	if ( !net_channel )
		return;

	// Source engine supa powerfow
	auto shiftable_ticks = g_globals.stored_ticks - net_channel->get_choked_packets( ) - time_to_ticks( net_channel->get_latency( 0 ) );

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
