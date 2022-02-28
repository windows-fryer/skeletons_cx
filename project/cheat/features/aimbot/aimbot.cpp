#include "aimbot.hpp"
#include "../../globals/globals.hpp"
#include "../../helpers/entity_list/entity_list.hpp"
#include <algorithm>

aimbot::aimbot_target get_best_entity( )
{
	// lil unoptimized, whatever
	aimbot::aimbot_target best_target;
	best_target.fov          = FLT_MAX;
	best_target.entity_index = -1;

	/* @blanket: i fucking hate sorting like this but we have to */
	for ( auto& player_info : g_entity_list.players ) {
		if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
			if ( !entity || !entity->is_alive( ) || !entity->is_enemy( g_globals.local ) )
				continue;

			const float entity_health       = entity->health( );
			const sdk::vector entity_origin = entity->origin( ); // origin is gay, whatever.
			const sdk::qangle angle_to_entity =
				math::vector_to_angle( entity_origin - ( g_globals.local->origin( ) + g_globals.local->view_offset( ) ) );
			const float fov_to_origin = math::calculate_angle_fov( g_globals.command->view_angles, angle_to_entity );

			// for dynamic selection use health multiplier to fov so aimbot priority is for low hp but aimbot also wants low fov
			if ( fov_to_origin < best_target.fov ) {
				best_target.fov          = fov_to_origin;
				best_target.entity_index = player_info.index;
			}
		}
	}

	return best_target;
}

// very basic for now.
void aimbot::impl::think( )
{
	if ( !g_globals.command ) // literally impossible
		return;

	if ( !( g_globals.command->buttons & sdk::in_attack ) )
		return;

	if ( !g_globals.local )
		return;

	// todo: check for ladder nigga -_-

	if ( !g_globals.local_weapon )
		return;

	// this function is sorta slow but well optimize it later
	auto best_entity = get_best_entity( );

	if ( best_entity.entity_index == -1 ) // no entity found
		return;

	sdk::c_tf_player* entity = g_interfaces.entity_list->get< sdk::c_tf_player >( best_entity.entity_index );

	[[unlikely]] if ( !entity ) return;

	// todo: hitbox selection
	sdk::vector hitbox_position = entity->get_hitbox_position( 0 ); // head only. whatever
	sdk::qangle angle_to_hitbox = math::vector_to_angle( hitbox_position - ( g_globals.local->origin( ) + g_globals.local->view_offset( ) ) );
	angle_to_hitbox.normalize( );

	g_globals.command->view_angles = angle_to_hitbox;
}