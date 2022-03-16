#include "antiaim.hpp"
#include "../../globals/global_vars.hpp"

void antiaim::impl::fakelag( sdk::c_user_cmd* cmd, bool& send_packet )
{
	if ( !g_interfaces.net_channel )
		return;

	if ( cmd->buttons & sdk::cmd_buttons::in_attack )
		return;

	int choked_packets = g_interfaces.net_channel->get_choked_packets( );
	int fakelag_max    = 24;

	send_packet = choked_packets == fakelag_max;
}

void antiaim::impl::do_180_sway( bool& send_packet )
{
	// todo: random

	if ( g_globals.command->buttons & sdk::in_attack ) {
		return;
	}
	//  bool sway_fake = true

	// ammount to add to yaw
	static float yaw_additive = 0.f;

	if ( send_packet ) {
		// nothing lel
	} else {
		g_globals.command->view_angles.yaw += 100.f;

		if ( yaw_additive >= 70.f )
			yaw_additive = 0.f;

		yaw_additive += 2.f;

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