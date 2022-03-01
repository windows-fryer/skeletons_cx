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