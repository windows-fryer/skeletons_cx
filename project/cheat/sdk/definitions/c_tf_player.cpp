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