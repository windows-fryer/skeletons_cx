#include "entity_list.hpp"

void entity_list::impl::update( )
{
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

	for ( int iterator = 0; iterator < 65; iterator++ ) {
		auto player = g_interfaces.entity_list->get< sdk::c_tf_player >( iterator );

		auto& player_info = players[ iterator ];

		player_info.valid = false;

		if ( !player || player == g_globals.local )
			continue;

		if ( player->is_player( ) ) {
			player_info.dormant_info.valid = false;

			if ( !player->is_alive( ) )
				continue;

			if ( player->is_dormant( ) ) {
				if ( ticks_to_time( g_interfaces.globals->tick_count - player_info.dormant_info.found_tick ) < 3.f )
					player_info.dormant_info.valid = true;

				continue;
			}

			if ( !player->is_enemy( g_globals.local ) )
				continue;

			player_info.valid = true;
			player_info.name  = player->name( );
			player_info.index = iterator;

			player_info.dormant_info.last_position = player->get_abs_origin( );
			player_info.dormant_info.found_tick    = g_interfaces.globals->tick_count;

			player_info.dormant_info.vouchable_position = player->get_abs_origin( );
			player_info.dormant_info.vouchable_tick     = g_interfaces.globals->tick_count;
		}
	}
}
