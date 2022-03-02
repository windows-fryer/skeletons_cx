#include "create_move.hpp"
#include "../../../features/include.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"

void __fastcall hooks::create_move::create_move_detour( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	create_move_hook.call_original( ecx, edx, sequence_number, input_sample_frametime, active );

	auto command  = g_interfaces.input->get_user_cmd( sequence_number );
	auto verified = &g_interfaces.input->get_verified_cmds( )[ sequence_number % 90 ];

	if ( !command || !verified )
		return;

	std::uintptr_t* _ebp;
	__asm mov _ebp, ebp;
	bool& send_packet = *reinterpret_cast< bool* >( *_ebp - 0x1 );

	auto net_chan            = reinterpret_cast< sdk::i_net_channel* >( g_interfaces.engine_client->get_net_channel_info( ) );
	g_interfaces.net_channel = net_chan;

	auto local_player = g_interfaces.entity_list->get< sdk::c_tf_player >( g_interfaces.engine_client->get_local_player( ) );

	if ( !local_player )
		return;

	const sdk::qangle old_angle = command->view_angles;
	g_globals.command           = command;

	g_antiaim.fakelag( command, send_packet );


	g_prediction.start( command, local_player );
	{
		g_aimbot.think( );
	}
	g_prediction.finish( command, local_player );

	g_movement.bunny_hop( );


	g_movement.move_fix( command, old_angle );

	verified->cmd = *command;
	verified->crc = command->get_checksum( );
}