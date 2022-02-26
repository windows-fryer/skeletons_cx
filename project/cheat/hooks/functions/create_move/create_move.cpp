#include "create_move.hpp"

void __fastcall hooks::create_move::create_move_detour( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	create_move_hook.call_original( ecx, edx, sequence_number, input_sample_frametime, active );

	auto command  = &g_interfaces.input->get_cmds( )[ sequence_number % 90 ];
	auto verified = &g_interfaces.input->get_verified_cmds( )[ sequence_number % 90 ];

	if ( !command || !verified )
		return;

	std::uintptr_t* _ebp;
	__asm mov _ebp, ebp;
	bool& send_packet = *reinterpret_cast< bool* >( *_ebp - 0x1 );

	g_globals.command = command;

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

		auto weapon_print_name = weapon->get_name( );

		console::log( "{}: {}\n", index, weapon_print_name );
	}

	verified->cmd = *command;
	verified->crc = command->get_checksum( );

	g_interfaces.input->get_cmds( )[ sequence_number % 90 ] = *command;
}