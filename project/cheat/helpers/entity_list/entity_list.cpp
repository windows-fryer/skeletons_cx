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

	if ( !local_player_entity )
		return;

	for ( int index = 0; index < g_interfaces.entity_list->get_highest_entity_index( ); index++ ) {
		auto entity = g_interfaces.entity_list->get< sdk::c_base_entity >( index );

		if ( !entity )
			continue;

		if ( index == local_player_index )
			continue;

		if ( entity->is_dormant( ) )
			continue;

		if ( entity->is_player( ) ) {
			auto player_entity = reinterpret_cast< sdk::c_tf_player* >( entity );

			if ( player_entity->is_alive( ) && player_entity->is_enemy( local_player_entity ) ) {
				sdk::player_info player_info;

				g_interfaces.engine_client->get_player_info( player_entity->entindex( ), &player_info );

				if ( player_info.name ) {
					auto new_player = player{ player_entity->entindex( ), std::string( player_info.name ) };

					players.push_back( new_player );
				}
			}
		}
	}
}
