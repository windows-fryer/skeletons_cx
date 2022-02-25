#include "interfaces.hpp"

void interfaces::impl::init( )
{
	std::vector< const char* > needed_modules = {
//		"client.dll",
		"engine.dll",
//		"localize.dll",
//		"materialsystem.dll",
//		"vguimatsurface.dll",
//		"vgui2.dll",
//		"shaderapidx9.dll",
//		"gameoverlayrenderer.dll",
//		"vphysics.dll",
//		"vstdlib.dll",
//		"tier0.dll",
//		"inputsystem.dll",
//		"studiorender.dll",
//		"datacache.dll",
//		"steam_api.dll",
//		"matchmaking.dll",
//		"server.dll",
//		"serverbrowser.dll",
//		"filesystem_stdio.dll",
	};

	for ( auto& module : needed_modules ) {
		auto create_interface = reinterpret_cast< std::uintptr_t >( get_proc_address( get_module_handle( module ), "CreateInterface" ) );

		while ( *reinterpret_cast< unsigned char* >( create_interface ) != 0xE9 )
			++create_interface;

		create_interface = jump_address( create_interface );

		while ( *reinterpret_cast< std::uint16_t* >( create_interface ) != 0x358B )
			++create_interface;

		auto node = **reinterpret_cast< interface_node*** >( create_interface + 0x2 );

		char buffer_name[ 128 ]{ };

		while ( node ) {
			std::size_t size{};

			for ( size = 0; node->name[ size ] != '\0'; ++size )
				buffer_name[ size ] = node->name[ size ];

			buffer_name[ size ] = '\0';

			interfaces.insert( std::make_pair( fnv( buffer_name ), reinterpret_cast< std::uintptr_t >( node->get( ) ) ) );

			node = node->next;
		}
	}
}

void interfaces::impl::shutdown( ) { }




std::uintptr_t interfaces::impl::jump_address( std::uintptr_t address )
{
	auto jump_relative = *reinterpret_cast< std::uintptr_t* >( address + 0x1 );

	jump_relative += 0x5;
	jump_relative += jump_relative;

	return address;
}
