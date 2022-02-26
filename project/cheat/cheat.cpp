#include "cheat.hpp"

void cheat::init( )
{
	modules::init( );
	console::init( );

	g_interfaces.init( );

	for ( int index = 0; index < 65; index++ ) {
		auto entity = g_interfaces.entity_list->get< sdk::c_base_entity >( index );

		if (!entity)
			continue;

		console::log( "{}\n", entity->simulation_time( ) );
	}
}

void cheat::shutdown( )
{
	modules::shutdown( );
	console::shutdown( );

	g_interfaces.shutdown( );
}