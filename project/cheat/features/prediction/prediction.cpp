#include "prediction.hpp"

void prediction::impl::start( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity )
{
	pred_backup.cur_time   = g_interfaces.globals->cur_time;
	pred_backup.frame_time = g_interfaces.globals->frame_time;
	pred_backup.tick_count = g_interfaces.globals->tick_count;
	pred_backup.tick_base  = entity->tick_base( );

	reset( );

	*reinterpret_cast< sdk::c_user_cmd** >( reinterpret_cast< uint32_t >( entity ) + 0x107C ) = cmd;
	set_prediction_random_seed( cmd );
	set_prediction_player( entity );

	const int tick_base = entity->tick_base( );

	g_interfaces.globals->tick_count = entity->tick_base( );
	g_interfaces.globals->cur_time   = entity->tick_base( ) * g_interfaces.globals->interval_per_tick;
	g_interfaces.globals->frame_time = g_interfaces.globals->interval_per_tick;

	const bool backup_is_first_time_predicted = g_interfaces.prediction->first_time_predicted;
	const bool backup_is_in_prediction        = g_interfaces.prediction->is_in_prediction;

	g_interfaces.prediction->first_time_predicted = false;
	g_interfaces.prediction->is_in_prediction        = true;

	static sdk::move_data_t move_data;

	g_interfaces.move_helper->set_host( entity );

	g_interfaces.game_movement->start_track_prediction_errors( entity );

	g_interfaces.prediction->set_local_view_angles( cmd->view_angles ); // not always wanted

	entity->pre_think( );


	g_interfaces.prediction->setup_move( entity, cmd, g_interfaces.move_helper, &move_data );
	g_interfaces.game_movement->process_movement( entity, &move_data );
	g_interfaces.prediction->finish_move( entity, cmd, &move_data );

	entity->post_think( );

	/* restore shit */
	entity->tick_base( )                             = pred_backup.tick_base;
	g_interfaces.prediction->first_time_predicted = backup_is_first_time_predicted;
	g_interfaces.prediction->is_in_prediction        = backup_is_in_prediction;
}


void prediction::impl::finish( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity )
{
	*reinterpret_cast< sdk::c_user_cmd** >( reinterpret_cast< uint32_t >( entity ) + 0x107C ) = nullptr;

	if(g_interfaces.globals->frame_time > 0.f)
		entity->tick_base()++;


	g_interfaces.game_movement->finish_track_prediction_errors( entity );

	set_prediction_player(nullptr);
	set_prediction_random_seed( nullptr );

	g_interfaces.globals->cur_time   = pred_backup.cur_time;
	g_interfaces.globals->frame_time = pred_backup.frame_time;
	g_interfaces.globals->tick_count = pred_backup.tick_count;

}



void prediction::impl::set_prediction_random_seed( sdk::c_user_cmd* cmd )
{
	static auto function = ( g_client_dll.pattern_scan( "55 8B EC 8B 45 ? 85 C0 75 ? C7 05" ).as< void ( * )( sdk::c_user_cmd* ) >( ) );
	function( cmd );
}

void prediction::impl::set_prediction_player( sdk::c_tf_player* entity )
{
	static auto predicted_player = *reinterpret_cast<sdk::c_tf_player**>(g_client_dll.pattern_scan( "83 3D ? ? ? ? ? 74 ? 6A ? 50" ).as< uintptr_t >( ));
	predicted_player = entity;
}

void prediction::impl::reset( )
{
	static auto function = ( g_client_dll.pattern_scan( "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3" ).as< void ( * )( ) >( ) );
	function( );
}