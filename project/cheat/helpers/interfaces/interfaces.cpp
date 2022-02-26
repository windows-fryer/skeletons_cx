#include "interfaces.hpp"

void interfaces::impl::init( )
{
	find_interfaces( );

	engine_client = reinterpret_cast< sdk::i_engine_client* >( interfaces[ fnv( "VEngineClient013" ) ] );
	base_client   = reinterpret_cast< sdk::i_base_client_dll* >( interfaces[ fnv( "VClient017" ) ] );
	entity_list   = reinterpret_cast< sdk::i_client_entity_list* >( interfaces[ fnv( "VClientEntityList003" ) ] );
	debug_overlay = reinterpret_cast< sdk::i_debug_overlay* >( interfaces[ fnv( "VDebugOverlay003" ) ] );
	input         = g_signatures[ "8B 0D ? ? ? ? FF 75 ? D9 45 ? 51 8B 01 D9 1C ? FF 75" ].add( 0x2 ).get( 2 ).as< sdk::i_input* >( );

	while ( !client_mode ) {
		const auto base_client_vtable = ( std::uint32_t* )( *( std::uint32_t* )( base_client ) );
		client_mode                   = **( sdk::i_client_mode*** )( ( std::uint32_t )( base_client_vtable[ 10 ] ) + 0x05 );
	}
}

void interfaces::impl::shutdown( ) { }

void interfaces::impl::find_interfaces( )
{
	std::vector< const char* > needed_modules = {
		"client.dll",
		"engine.dll",
		"localize.dll",
		"materialsystem.dll",
		"vguimatsurface.dll",
		"vgui2.dll",
		"shaderapidx9.dll",
		"gameoverlayrenderer.dll",
		"vphysics.dll",
		"vstdlib.dll",
		"tier0.dll",
		"inputsystem.dll",
		"studiorender.dll",
		"datacache.dll",
		"steam_api.dll",
		"matchmaking.dll",
		"server.dll",
		"serverbrowser.dll",
		"filesystem_stdio.dll",
	};

	for ( auto& module : needed_modules ) {
		auto create_interface = reinterpret_cast< std::uintptr_t >( get_proc_address( get_module_handle( module ), "CreateInterface" ) );

		if ( !create_interface )
			continue;

		while ( *reinterpret_cast< std::uint8_t* >( create_interface ) != 0xE9 )
			++create_interface;

		create_interface = jump_address( create_interface );

		while ( *reinterpret_cast< std::uint16_t* >( create_interface ) != 0x358B )
			++create_interface;

		auto node = **reinterpret_cast< interface_node*** >( create_interface + 0x2 );

		char buffer_name[ 128 ]{ };

		while ( node ) {
			std::size_t size{ };

			for ( size = 0; node->name[ size ] != '\0'; ++size )
				buffer_name[ size ] = node->name[ size ];

			buffer_name[ size ] = '\0';

			interfaces.insert( std::make_pair( fnv( buffer_name ), reinterpret_cast< std::uintptr_t >( node->get( ) ) ) );

			node = node->next;
		}
	}
}

std::uintptr_t interfaces::impl::jump_address( std::uintptr_t address )
{
	auto jump_relative = *reinterpret_cast< std::uintptr_t* >( address + 0x1 );

	address += 0x5;
	address += jump_relative;

	return address;
}
