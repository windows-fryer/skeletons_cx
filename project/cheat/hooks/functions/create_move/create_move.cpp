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

	if ( !g_globals.local || !g_globals.local_weapon )
		return;

	const sdk::qangle old_angle = command->view_angles;
	g_globals.command           = command;

	if ( g_globals.shifting && !( command->buttons & sdk::in_attack ) )
		command->buttons |= sdk::in_attack;

	//	g_antiaim.fakelag( command, send_packet );

	g_prediction.start( command, g_globals.local );
	{
		g_globals.can_primary_attack   = g_globals.local_weapon->can_attack_primary( g_globals.local );
		g_globals.can_secondary_attack = g_globals.local_weapon->can_attack_secondary( g_globals.local );

		g_aimbot.think( );
		//		g_antiaim.do_180_sway( send_packet );
	}
	g_prediction.finish( command, g_globals.local );

	g_movement.bunny_hop( );

	g_movement.move_fix( command, old_angle );

	g_antiaim.update_fake( send_packet );

	if ( g_globals.shifting )
		send_packet = !g_globals.choke;

	verified->cmd = *command;
	verified->crc = command->get_checksum( );
}