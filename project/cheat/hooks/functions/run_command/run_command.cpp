#include "run_command.hpp"
#include <algorithm>

void hooks::run_command::run_command_detour( void* ecx, void* edx, sdk::c_base_player* player, sdk::c_user_cmd* command, void* move_helper )
{
	// Like literally can't happen lol.
	[[unlikely]] if ( !player || player != g_globals.local || !g_globals.local_weapon || !g_globals.local ||
	                  !g_interfaces.net_channel ) return run_command_hook.call_original( ecx, edx, player, command, move_helper );

	run_command_hook.call_original( ecx, edx, player, command, move_helper );
}
