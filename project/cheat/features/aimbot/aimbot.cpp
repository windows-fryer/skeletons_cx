#include "aimbot.hpp"
#include "../../globals/globals.hpp"
#include "../../helpers/entity_list/entity_list.hpp"
#include "../lagcomp/lagcomp.hpp"
#include "../prediction/prediction.hpp"
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
			const sdk::vector entity_origin = entity->get_abs_origin( ); // origin is gay, whatever.
			const sdk::qangle angle_to_entity =
				math::vector_to_angle( entity_origin - ( g_globals.local->get_abs_origin( ) + g_globals.local->view_offset( ) ) );
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

// def so we dont have to spam this homosexually
#define AIMBOT_RETURN                                                                                                                                \
	{                                                                                                                                                \
		g_globals.lagcomp_record = nullptr;                                                                                                          \
		return;                                                                                                                                      \
	}

// very basic for now.
void aimbot::impl::think( )
{
	// literally impossible
	[[unlikely]] if ( !g_globals.command ) return;

	if ( !g_globals.local || !g_globals.local_weapon )
		AIMBOT_RETURN;

	if ( !( g_globals.command->buttons & sdk::in_attack ) )
		return;

	auto best_entity = get_best_entity( );

	// no entity found
	if ( best_entity.entity_index == -1 )
		return;

	sdk::c_tf_player* entity = g_interfaces.entity_list->get< sdk::c_tf_player >( best_entity.entity_index );

	// unlikely because entity will be neg 1 if none is found & we already check for that above
	[[unlikely]] if ( !entity ) return;

	/* weapon is non-projectile */
	if ( !weapon_is_projectile( g_globals.local_weapon ) ) {
		g_lagcomp.backtrack_player( entity );

		[[unlikely]] if ( !g_globals.lagcomp_record ) return;

		// todo: hitbox selection
		sdk::vector hitbox_position = entity->get_hitbox_position( 0, g_globals.lagcomp_record->bone_matrix ); // head only. whatever - shut up nigger
		sdk::qangle angle_to_hitbox = math::vector_to_angle( hitbox_position - g_globals.local->eye_position( ) );
		// angle_to_hitbox.normalize( );

		g_globals.command->view_angles = angle_to_hitbox;
	} else {
		auto weapon_info = get_weapon_info( g_globals.local_weapon );

		static auto gravity_cvar = g_interfaces.cvar->find_var( "sv_gravity" );

		float time_to_hit = g_globals.local->eye_position( ).dist_to( entity->get_abs_origin( ) ) / weapon_info.speed;
		sdk::vector position;

		g_prediction.projectile_backup( entity );

		for ( int tick = 0; tick < time_to_ticks( time_to_hit ); tick++ ) {
			position = g_prediction.projectile_run( entity );
		}

		g_prediction.projectile_restore( entity );

		time_to_hit = g_globals.local->eye_position( ).dist_to( position ) / weapon_info.speed;

		sdk::vector final_position;

		g_prediction.projectile_backup( entity );

		for ( int tick = 0; tick < time_to_ticks( time_to_hit ); tick++ ) {
			final_position = g_prediction.projectile_run( entity );
		}

		final_position.x -= 4.f;
		final_position.y -= 4.f;
		final_position.z += 10.f;

		g_prediction.projectile_restore( entity );

		sdk::qangle angle_to_hitbox = math::vector_to_angle( final_position - g_globals.local->eye_position( ) );
		angle_to_hitbox.normalize( );

		g_globals.command->view_angles = angle_to_hitbox;
	}
}
bool aimbot::impl::weapon_is_projectile( sdk::c_tf_weapon_base* weapon )
{
	switch ( weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctfrocketlauncher_directhit:
		return true;
	case sdk::e_class_ids::ctfrocketlauncher:
		return true;
	default:
		return false;
	}
}
aimbot::weapon_info aimbot::impl::get_weapon_info( sdk::c_tf_weapon_base* weapon )
{
	switch ( weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctfrocketlauncher_directhit:
		return { 0.f, 1980.f, false };
	case sdk::e_class_ids::ctfrocketlauncher:
		return { 0.f, 1100.f, false };
	default:
		return { };
	}
}
