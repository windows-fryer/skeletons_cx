#include "create_move.hpp"
#include "../../../features/include.hpp"

void __fastcall hooks::create_move::create_move_detour( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	create_move_hook.call_original( ecx, edx, sequence_number, input_sample_frametime, active );

	auto command  = &g_interfaces.input->get_cmds( )[ sequence_number % 90 ];
	auto verified = &g_interfaces.input->get_verified_cmds( )[ sequence_number % 90 ];

	[[unlikely]] if ( !command || !verified ) return;

	std::uintptr_t* _ebp;
	__asm mov _ebp, ebp;
	bool& send_packet = *reinterpret_cast< bool* >( *_ebp - 0x1 );

	g_globals.command           = command;
	const sdk::qangle old_angle = command->view_angles;

	for ( int index = 0; index < 65; index++ ) {
		auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( index );

		if ( !entity || !entity->is_player( ) )
			continue;

		auto weapon_handle = entity->active_weapon( );

		if ( !weapon_handle.index )
			continue;

		auto weapon = g_interfaces.entity_list->get< sdk::c_tf_weapon_base >( weapon_handle );

		if ( !weapon )
			continue;
	}

	command->view_angles.normalize( );
	g_movement.move_fix( command, old_angle );

	verified->cmd = *command;
	verified->crc = command->get_checksum( );

	g_interfaces.input->get_cmds( )[ sequence_number % 90 ] = *command;
}