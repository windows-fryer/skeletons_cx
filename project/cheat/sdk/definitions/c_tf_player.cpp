#include "../structs/c_tf_player.hpp"
#include "../../helpers/interfaces/interfaces.hpp"

void sdk::c_tf_player::pre_think( )
{
	static auto pre_think = g_signatures[ "56 8B F1 8B 06 FF 90 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 8B CE" ].as< void( __thiscall* )( void* ) >( );
	pre_think( this );
}

void sdk::c_tf_player::post_think( )
{
	static auto post_think = g_signatures[ "53 56 8B 35 ? ? ? ? 8B D9 8B CE 8B 06" ].as< void( __thiscall* )( void* ) >( );
	post_think( this );
}


bool sdk::c_tf_player::can_hit( const vector pos )
{
	sdk::c_game_trace trace;
	sdk::c_trace_filter_world_and_props_only filter;
	sdk::ray_t ray;
	ray.init(this->eye_position(), pos);

	/* no def for mask_shot yet, too lazy */
	g_interfaces.engine_trace->trace_ray(ray, (0x1 | 0x4000 | 0x2000000 | 0x2 | 0x4000000 | 0x40000000), &filter, &trace);

	return trace.fraction == 1.f;
}

void sdk::c_tf_player::draw_client_hitbox( const float& duration )
{
	auto hdr = g_interfaces.model_info->get_studio_model( get_model( ) );

	if ( !hdr )
		return;

	auto set = hdr->get_hitbox_set( hitbox_set( ) );

	if ( !set )
		return;

	matrix_3x4 bone_matrix[ 128 ];
	if ( !setup_bones( bone_matrix, 128, 0x0007FF00, 0 ) ) // bone used by anything
		return;

	vector position;
	qangle angle;

	for ( int i = 0; i < set->num_hitboxes; i++ ) {
		auto box = set->get_hitbox( i );

		angle    = bone_matrix[ box->bone ].to_angle( );
		position = bone_matrix[ box->bone ].to_vector( 3 );

		g_interfaces.debug_overlay->add_box_overlay( position, box->bb_min, box->bb_max, angle, 255, 50, 0, 0, duration );
	}
}

sdk::c_base_animating* sdk::c_tf_player::get_server_base_animating( )
{
	// You're such a stupid nigger holy shit, "Why doesn't it work when I don't use __cdecl* and my return type is wrong!??!?!?" I WONDER WHY YOU
	// FUCKING IDIOT JESUS FUCKING CHRIST
	static auto server_base_animating =
		g_signatures[ "55 8B EC 8B 55 ? 85 D2 7E ? A1" ]
			.as< sdk::c_base_animating*( __cdecl* )( int ) >( ); // amazing fucking function wont let me do jack shit -_-

	return server_base_animating( entindex( ) );
}