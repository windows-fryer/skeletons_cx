#include "animations.hpp"

void animations::impl::on_update_clientside_anims( sdk::c_tf_player* entity, float& yaw, float& pitch )
{
	/* get ticks choked by entity */
	int ticks_choked = time_to_ticks( ( entity->simulation_time( ) - entity->get_old_simulation_time( ) ) );

	sdk::qangle current_angle = entity->get_abs_angles( );
	// float current_pitch = entity->eye_angles_x( );
	// float current_yaw   = entity->eye_angles_y( );

	/* 2 ticks of fake lag = resolver go crazy, resolve, p, kill, ez. */
	if ( ticks_choked > 1 ) {
		/* pitch */
		{
			// -90.f, 90
			if ( current_angle.pitch != pitch )              // maybe jittering real pitch?
				pitch = ( current_angle.pitch + pitch ) / 2; // lel, safer than going for up pitch
		}

		/* do yaw */
		{
			// apply average
			float yaw_average        = ( yaw + current_angle.yaw ) / 2;
			const float tick_gayness = 2.f; // slight random
			float semi_predicted_yaw = yaw_average + ( ( float )ticks_choked * tick_gayness );
			yaw                      = semi_predicted_yaw;
		}
	}
}