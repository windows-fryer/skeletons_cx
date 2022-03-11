#include "run_command.hpp"
#include <algorithm>

void hooks::run_command::run_command_detour( void* ecx, void* edx, sdk::c_base_player* player, sdk::c_user_cmd* command, void* move_helper )
{
	// Like literally can't happen lol.
	[[unlikely]] if ( player != g_globals.local || !g_globals.local_weapon || !g_globals.local ||
	                  !g_interfaces.net_channel ) return run_command_hook.call_original( ecx, edx, player, command, move_helper );

	static auto clock_correction = g_interfaces.cvar->find_var( "sv_clockcorrection_msecs" );
	float correction_ticks       = time_to_ticks( std::clamp( clock_correction->get_float( ) / 1000.f, 0.f, 1.f ) );

	int ideal_final_tick     = g_interfaces.globals->tick_count + correction_ticks;
	int estimated_final_tick = player->tick_base( ) + 1;

	int too_fast_limit = ideal_final_tick + correction_ticks;
	int too_slow_limit = ideal_final_tick - correction_ticks;

	if ( estimated_final_tick > too_fast_limit || estimated_final_tick < too_slow_limit ) {
		int corrected_tick = ideal_final_tick - 1 + g_interfaces.globals->sim_ticks_this_frame;

		player->tick_base( ) = corrected_tick;
	}

	run_command_hook.call_original( ecx, edx, player, command, move_helper );
}
