#include "antiaim.hpp"

//#define fuck_mode

void antiaim::impl::fakelag( sdk::c_user_cmd* cmd, bool& send_packet )
{
	if ( !g_interfaces.net_channel )
		return;

	if ( cmd->buttons & sdk::cmd_buttons::in_attack )
		return;

	const int num_choked_ticks = g_interfaces.net_channel->get_choked_packets( );

#ifdef fuck_mode
	// fluctuate
	static int fakelag_goal = 0;
	const int fakelag_max   = 6;
	if ( num_choked_ticks == fakelag_goal ) {
		if ( fakelag_goal == fakelag_max )
			fakelag_goal = 0;

		fakelag_goal++;
		send_packet = true;

	} else {
		send_packet = false;
	}
	return;
#endif

	send_packet = num_choked_ticks <= 6;
}