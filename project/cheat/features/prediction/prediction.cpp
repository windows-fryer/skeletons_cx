#include "prediction.hpp"
#include "../../globals/global_vars.hpp"

void prediction::impl::start( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity )
{
	/* update local data */
	unpredicted_local_data.flags = entity->flags();

	pred_backup.cur_time   = g_interfaces.globals->cur_time;
	pred_backup.frame_time = g_interfaces.globals->frame_time;
	pred_backup.tick_count = g_interfaces.globals->tick_count;
	pred_backup.tick_base  = entity->tick_base( );

	reset( );

	entity->current_command( ) = cmd;
	set_prediction_random_seed( cmd );
	set_prediction_player( entity );

	const int tick_base = entity->tick_base( );

	g_interfaces.globals->tick_count = entity->tick_base( );
	g_interfaces.globals->cur_time   = entity->tick_base( ) * g_interfaces.globals->interval_per_tick;
	g_interfaces.globals->frame_time = g_interfaces.globals->interval_per_tick;

	const bool backup_is_first_time_predicted = g_interfaces.prediction->first_time_predicted;
	const bool backup_is_in_prediction        = g_interfaces.prediction->is_in_prediction;

	g_interfaces.prediction->first_time_predicted = false;
	g_interfaces.prediction->is_in_prediction     = true;

	static sdk::move_data_t move_data;

	g_interfaces.move_helper->set_host( entity );

	g_interfaces.game_movement->start_track_prediction_errors( entity );

	g_interfaces.prediction->set_local_view_angles( cmd->view_angles ); // not always wanted

	entity->pre_think( );

	g_interfaces.prediction->setup_move( entity, cmd, g_interfaces.move_helper, &move_data );
	g_interfaces.game_movement->process_movement( entity, &move_data );
	g_interfaces.prediction->finish_move( entity, cmd, &move_data );

	entity->post_think( );

	entity->tick_base( )                          = pred_backup.tick_base;
	g_interfaces.prediction->first_time_predicted = backup_is_first_time_predicted;
	g_interfaces.prediction->is_in_prediction     = backup_is_in_prediction;

	/* update local data */
	predicted_local_data.flags = entity->flags();
}

void prediction::impl::finish( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity )
{
	entity->current_command( ) = nullptr;

	if ( g_interfaces.globals->frame_time > 0.f )
		entity->tick_base( )++;

	g_interfaces.game_movement->finish_track_prediction_errors( entity );

	g_interfaces.move_helper->set_host( nullptr );
	set_prediction_player( nullptr );
	set_prediction_random_seed( nullptr );

	g_interfaces.globals->cur_time   = pred_backup.cur_time;
	g_interfaces.globals->frame_time = pred_backup.frame_time;
	g_interfaces.globals->tick_count = pred_backup.tick_count;
}

void prediction::impl::set_prediction_random_seed( sdk::c_user_cmd* cmd )
{
	static auto set_prediction_random_seed = g_signatures[ "55 8B EC 8B 45 ? 85 C0 75 ? C7 05" ].as< void ( * )( sdk::c_user_cmd* ) >( );
	set_prediction_random_seed( cmd );
}

void prediction::impl::set_prediction_player( sdk::c_tf_player* entity )
{
	static auto predicted_player = g_signatures[ "83 3D ? ? ? ? ? 74 ? 6A ? 50" ].get( 1 ).as< sdk::c_tf_player* >( );
	predicted_player             = entity;
}

void prediction::impl::reset( )
{
	static auto reset = g_signatures[ "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3" ].as< void ( * )( ) >( );
	reset( );
}
void prediction::impl::projectile_backup( sdk::c_tf_player* entity )
{
	entity->current_command( ) = &fake_cmd;

	pred_proj_backup.origin          = entity->origin( );
	pred_proj_backup.base_velocity   = entity->base_velocity( );
	pred_proj_backup.duck_jump_time  = entity->duck_jump_time( );
	pred_proj_backup.duck_time       = entity->duck_timer( );
	pred_proj_backup.ducked          = entity->ducked( );
	pred_proj_backup.ducking         = entity->ducking( );
	pred_proj_backup.flags           = entity->flags( );
	pred_proj_backup.ground_entity   = entity->ground_entity( );
	pred_proj_backup.in_duck_jump    = entity->in_duck_jump( );
	pred_proj_backup.model_scale     = entity->model_scale( );
	pred_proj_backup.velocity        = entity->estimate_abs_velocity( );
	pred_proj_backup.simulation_time = entity->simulation_time( );

	pred_backup.is_in_prediction   = g_interfaces.prediction->is_in_prediction;
	pred_backup.first_time_running = g_interfaces.prediction->first_time_predicted;
	pred_backup.frame_time         = g_interfaces.globals->frame_time;
	pred_backup.tick_base          = entity->tick_base( );
	pred_backup.cur_time           = g_interfaces.globals->cur_time;

	if ( entity->flags( ) & sdk::ducking ) {
		entity->flags( ) &= ~sdk::ducking;
		entity->ducked( )         = true;
		entity->ducktime( )       = 0.f;
		entity->duck_jump_time( ) = 0.f;
		entity->ducking( )        = false;
		entity->in_duck_jump( )   = false;
	}

	entity->ground_entity( ) = { };

	entity->model_scale( ) -= 0.03125f;

	if ( entity->flags( ) & sdk::onground )
		entity->origin( ).z += 0.03125f;

	if ( fabsf( entity->velocity( ).x ) < 0.01f )
		entity->velocity( ).x = 0.015f;

	if ( fabsf( entity->velocity( ).y ) < 0.01f )
		entity->velocity( ).y = 0.015f;

	fake_move_data.first_run_of_functions = false;
	fake_move_data.game_code_moved_player = false;
	fake_move_data.player_handle          = entity->get_ref_e_handle( );
	fake_move_data.velocity               = entity->estimate_abs_velocity( );
	fake_move_data.abs_origin             = entity->get_abs_origin( );

	fake_move_data.view_angles = { 0.f, velocity_to_angles( entity->velocity( ) ).yaw, 0.f };

	sdk::vector forward, right, up;

	math::angle_to_vector( fake_move_data.view_angles, &forward, &right, &up );

	fake_move_data.forward_move =
		( fake_move_data.velocity.y - right.y / right.x * fake_move_data.velocity.x ) / ( forward.y - right.y / right.x * forward.x );
	fake_move_data.side_move = ( fake_move_data.velocity.x - forward.x * fake_move_data.forward_move ) / right.x;
}

sdk::vector prediction::impl::projectile_run( sdk::c_tf_player* entity )
{
	g_interfaces.prediction->is_in_prediction     = true;
	g_interfaces.prediction->first_time_predicted = true;
	g_interfaces.globals->frame_time              = g_interfaces.prediction->engine_paused ? 0.f : g_interfaces.globals->interval_per_tick;

	g_interfaces.game_movement->process_movement( entity, &fake_move_data );

	return fake_move_data.abs_origin;
}

void prediction::impl::projectile_restore( sdk::c_tf_player* entity )
{
	entity->current_command( ) = nullptr;

	entity->origin( )          = pred_proj_backup.origin;
	entity->base_velocity( )   = pred_proj_backup.base_velocity;
	entity->duck_jump_time( )  = pred_proj_backup.duck_jump_time;
	entity->duck_timer( )      = pred_proj_backup.duck_time;
	entity->ducked( )          = pred_proj_backup.ducked;
	entity->ducking( )         = pred_proj_backup.ducking;
	entity->flags( )           = pred_proj_backup.flags;
	entity->ground_entity( )   = pred_proj_backup.ground_entity;
	entity->in_duck_jump( )    = pred_proj_backup.in_duck_jump;
	entity->model_scale( )     = pred_proj_backup.model_scale;
	entity->velocity( )        = pred_proj_backup.velocity;
	entity->simulation_time( ) = pred_proj_backup.simulation_time;
	entity->tick_base( )       = pred_backup.tick_base;

	g_interfaces.prediction->is_in_prediction     = pred_backup.is_in_prediction;
	g_interfaces.prediction->first_time_predicted = pred_backup.first_time_running;
	g_interfaces.globals->frame_time              = pred_backup.frame_time;
	g_interfaces.globals->cur_time                = pred_backup.cur_time;

	memset( &fake_move_data, 0, sizeof( sdk::move_data_t ) );
	memset( &pred_proj_backup, 0, sizeof( prediction_projectile_backup ) );
}

sdk::qangle prediction::impl::velocity_to_angles( sdk::vector direction )
{
	float yaw, pitch;

	if ( direction.y == 0.f && direction.x == 0.f ) {
		yaw = 0.f;

		if ( direction.z > 0.f )
			pitch = 270.f;
		else
			pitch = 90.f;
	} else {
		yaw   = RAD2DEG( atan2f( direction.y, direction.x ) );
		pitch = RAD2DEG( atan2f( -direction.x, sqrtf( direction.dot( direction ) ) ) );

		if ( yaw < 0.f )
			yaw += 360.f;

		if ( pitch < 0.f )
			pitch += 360.f;
	}

	return { pitch, yaw, 0.f };
}
