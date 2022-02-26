#include "entity_list.hpp"

void entity_list::impl::update( )
{
	players.clear( );
	buildings.clear( );

	g_globals.local        = nullptr;
	g_globals.local_weapon = nullptr;

	auto local_player_index  = g_interfaces.engine_client->get_local_player( );
	auto local_player_entity = g_interfaces.entity_list->get< sdk::c_tf_player >( local_player_index );

	if ( local_player_entity ) {
		g_globals.local = local_player_entity;

		auto local_player_weapon_handle = local_player_entity->active_weapon( );

		if ( local_player_weapon_handle.index ) {
			auto local_player_weapon_entity = g_interfaces.entity_list->get< sdk::c_tf_weapon_base >( local_player_weapon_handle );

			if ( local_player_weapon_entity )
				g_globals.local_weapon = local_player_weapon_entity;
		}
	}

	for ( int index = 0; index < g_interfaces.entity_list->get_highest_entity_index( ); index++ ) {
		auto entity = g_interfaces.entity_list->get< sdk::c_base_entity >( index );

		if ( !entity )
			continue;

		if ( entity->is_player( ) ) {
			if ( local_player_entity ) {
				if ( local_player_entity->team_num( ) != entity->team_num( ) ) { }
			}
		}
	}
}
