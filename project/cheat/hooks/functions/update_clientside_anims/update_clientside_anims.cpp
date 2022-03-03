#include "update_clientside_anims.hpp"
#include "../../../features/include.hpp"

void __fastcall hooks::update_clientside_anims::update_clientside_anims_detour( void* _ecx, void* _edx, float yaw, float pitch )
{
	auto entity = reinterpret_cast< sdk::c_tf_player* >( _ecx );

	if ( !g_globals.local || !g_globals.local->is_alive( ) )
		return update_clientside_anims_hook.call_original( _ecx, _edx, yaw, pitch );

	if ( entity->is_enemy( g_globals.local ) ) {
		/* yes */
		int ticks_choked = time_to_ticks( ( entity->simulation_time( ) - entity->get_old_simulation_time( ) ) );

		/* 2 ticks of fake lag = resolver go crazy, resolve, p, kill, ez. */
		if ( ticks_choked > 1 ) {
			sdk::qangle current_angle = entity->get_abs_angles( );
			const float current_yaw   = current_angle.yaw;
			const float current_pitch = current_angle.pitch;

			/* do the pitch */
			{
				// -90.f, 90
				if ( current_pitch != pitch ) // maybe jittering real pitch?
					pitch = ( current_pitch + pitch ) / 2; // lel
			}

			/* do yaw */
			{


			}
		}
	}

	return update_clientside_anims_hook.call_original( _ecx, _edx, yaw, pitch );
}
