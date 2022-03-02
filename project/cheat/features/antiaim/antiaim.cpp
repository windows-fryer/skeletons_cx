#include "antiaim.hpp"
#include "../../globals/global_vars.hpp"

#define fuck_mode

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

void antiaim::impl::do_180_sway( bool& send_packet )
{
	// todo: random

	//  bool sway_fake = true

	// ammount to add to yaw
	static float yaw_additive = 0.f;

	if ( send_packet ) {
		// nothing lel
	} else {
		/* again, readable code > fast code | since the compiler will just speed this thang up */

		/* fake in opposite direction */
		g_globals.command->view_angles.yaw += 90.f; // 180.f;

		/* sway yaw 60 degrees */
		if ( yaw_additive >= 60.f )
			yaw_additive = 0.f;

		/* increment by however much */
		yaw_additive += 2.f;

		/* add yaw additive */
		g_globals.command->view_angles.yaw += yaw_additive;
	}
}

void antiaim::impl::update_fake( bool& send_packet )
{
	// todo: setupbones shit and actual proper anim shit
	if ( send_packet ) {
		local_real_angle = g_globals.command->view_angles;
	} else {
	}
}