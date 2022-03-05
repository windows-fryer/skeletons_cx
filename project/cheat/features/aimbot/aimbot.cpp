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
		if ( player_info.valid ) {
			if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
				if ( !entity )
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
		AIMBOT_RETURN

	if ( !( g_globals.command->buttons & sdk::in_attack ) ) {
		if ( !should_be_aiming && attack_next_tick( g_globals.local_weapon ) && !attacked )
			should_be_aiming = true;
		else
			AIMBOT_RETURN
	}

	attacked = false;

	auto best_entity = get_best_entity( );

	// no entity found
	if ( best_entity.entity_index == -1 )
		AIMBOT_RETURN

	sdk::c_tf_player* entity = g_interfaces.entity_list->get< sdk::c_tf_player >( best_entity.entity_index );

	// unlikely because entity will be neg 1 if none is found & we already check for that above
	[[unlikely]] if ( !entity ) AIMBOT_RETURN;

	/* weapon is non-projectile */
	if ( !weapon_is_projectile( g_globals.local_weapon ) ) {
		g_lagcomp.backtrack_player( entity );

		[[unlikely]] if ( !g_globals.lagcomp_record ) return;

		// todo: hitbox selection
		sdk::vector hitbox_position = entity->get_hitbox_position( 0, g_globals.lagcomp_record->bone_matrix ); // head only. whatever - shut up nigger
		sdk::qangle angle_to_hitbox = math::vector_to_angle( hitbox_position - g_globals.local->eye_position( ) );

		// sdk::c_game_trace trace;
		// sdk::c_trace_filter_world_and_props_only filter;
		// sdk::ray_t ray;
		// ray.init( g_globals.local->eye_position( ), hitbox_position );
		// g_interfaces.engine_trace->trace_ray( ray, MASK_SHOT, &filter, &trace );

		// std::cout << trace.fraction << '\n';
		if ( g_globals.local->can_hit( hitbox_position ) )
			g_globals.command->view_angles = angle_to_hitbox;
	} else {
		auto weapon_info = get_weapon_info( g_globals.local_weapon );

		static auto gravity_cvar = g_interfaces.cvar->find_var( "sv_gravity" );

		float time_to_hit   = g_globals.local->eye_position( ).dist_to( entity->get_abs_origin( ) ) / weapon_info.speed;
		auto old_abs_origin = entity->get_abs_origin( );

		sdk::vector position;

		g_prediction.projectile_backup( entity );

		for ( int tick = 0; tick < time_to_ticks( time_to_hit ); tick++ ) {
			position = g_prediction.projectile_run( entity );
		}

		g_prediction.projectile_restore( entity );

		time_to_hit = g_globals.local->eye_position( ).dist_to( position ) / weapon_info.speed;

		g_prediction.projectile_backup( entity );

		for ( int tick = 0; tick < time_to_ticks( time_to_hit ); tick++ ) {
			position = g_prediction.projectile_run( entity );
		}

		g_prediction.projectile_restore( entity );

		entity->set_abs_origin( position );
		entity->invalidate_bone_cache( );

		position = weapon_info.hitbox == -1 ? entity->get_abs_origin( ) : entity->get_hitbox_position( weapon_info.hitbox );

		sdk::qangle angle_to_hitbox = math::vector_to_angle( position - g_globals.local->eye_position( ) );
		angle_to_hitbox.normalize( );

		if ( weapon_info.curves ) {
			auto arch_info = calculate_arch( g_globals.local->eye_position( ), position, g_globals.command->view_angles, weapon_info );

			time_to_hit = arch_info.time;

			g_prediction.projectile_backup( entity );

			for ( int tick = 0; tick < time_to_ticks( time_to_hit ); tick++ ) {
				position = g_prediction.projectile_run( entity );
			}

			g_prediction.projectile_restore( entity );

			entity->set_abs_origin( position );
			entity->invalidate_bone_cache( );

			position = weapon_info.hitbox == -1 ? entity->get_abs_origin( ) : entity->get_hitbox_position( weapon_info.hitbox );

			arch_info = calculate_arch( g_globals.local->eye_position( ), position, g_globals.command->view_angles, weapon_info );

			angle_to_hitbox.pitch = -RAD2DEG( arch_info.pitch );
			angle_to_hitbox.yaw   = RAD2DEG( arch_info.yaw );
			angle_to_hitbox.normalize( );
		}

		if ( g_globals.local->can_hit( position ) && ( attack_next_tick( g_globals.local_weapon ) ? should_be_aiming : true ) ) {
			g_globals.command->view_angles = angle_to_hitbox;
			attacked                       = true;
		}

		should_be_aiming = false;

		entity->set_abs_origin( old_abs_origin );
		entity->invalidate_bone_cache( );
	}
}

bool aimbot::impl::weapon_is_projectile( sdk::c_tf_weapon_base* weapon )
{
	switch ( weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctfrocketlauncher_directhit:
		return true;
	case sdk::e_class_ids::ctfrocketlauncher:
		return true;
	case sdk::e_class_ids::ctfgrenadelauncher:
		return true;
	case sdk::e_class_ids::ctfcompoundbow:
		return true;
	default:
		return false;
	}
}
aimbot::weapon_info aimbot::impl::get_weapon_info( sdk::c_tf_weapon_base* weapon )
{
	switch ( weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctfrocketlauncher_directhit:
		return { 0.f, 1980.f, false, -1 };
	case sdk::e_class_ids::ctfrocketlauncher:
		return { 0.f, 1100.f, false, -1 };
	case sdk::e_class_ids::ctfgrenadelauncher:
		return { 0.4f, 1216.6f, true, sdk::hitbox_chest };
	case sdk::e_class_ids::ctfcompoundbow: {
		auto casted_weapon = reinterpret_cast< sdk::c_tf_pipebomb_launcher* >( weapon );
		auto charge        = g_interfaces.globals->cur_time - casted_weapon->charge_begin_time( );

		return { ( ( fminf( fmaxf( charge, 0.0f ), 1.0f ) * -0.4f ) + 0.5f ), ( ( fminf( fmaxf( charge, 0.0f ), 1.0f ) * 800.0f ) + 1800.0f ), true,
			     sdk::hitbox_head };
	}
	default:
		return { };
	}
}
aimbot::proj_solution aimbot::impl::calculate_arch( sdk::vector origin, sdk::vector point, sdk::qangle view_angles, weapon_info info )
{
	static auto gravity_cvar = g_interfaces.cvar->find_var( "sv_gravity" );

	aimbot::proj_solution out{ };

	auto v   = point - origin;
	float dx = sqrt( v.x * v.x + v.y * v.y );
	float dy = v.z;
	float v0 = info.speed;

	if ( float g = gravity_cvar->get_float( ) * info.gravity ) {
		float root = v0 * v0 * v0 * v0 - g * ( g * dx * dx + 2.0f * dy * v0 * v0 );

		out.pitch = atan( ( v0 * v0 - sqrt( root ) ) / ( g * dx ) );
		out.yaw   = atan2( v.y, v.x );
	}

	out.time = dx / ( cos( out.pitch ) * v0 );

	return out;
}
bool aimbot::impl::attack_next_tick( sdk::c_tf_weapon_base* weapon )
{
	switch ( weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctfrocketlauncher_directhit:
		return false;
	case sdk::e_class_ids::ctfrocketlauncher:
		return false;
	case sdk::e_class_ids::ctfgrenadelauncher:
		return false;
	case sdk::e_class_ids::ctfcompoundbow:
		return true;
	default:
		return false;
	}
}
