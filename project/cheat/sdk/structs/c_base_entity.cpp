#include "c_base_entity.hpp"
#include "../../helpers/interfaces/interfaces.hpp"
#include "../../helpers/modules/modules.hpp"

void sdk::c_base_entity::get_bone_position( std::uint32_t bone_index, vector* position, qangle* angles )
{
	static auto function =
		g_engine_dll
			.pattern_scan( "55 8b ec 83 ec ? 56 8b f1 80 be ? ? ? ? ? 75 ? 83 be ? ? ? ? ? 75 ? e8 ? ? ? ? 85 c0 74 ? 8b ce e8 ? ? ? ? 8b 86" )
			.as< std::uintptr_t >( );

	using fn_get_bone_position = void( __thiscall* )( void*, vector*, qangle* );

	reinterpret_cast< fn_get_bone_position >( function )( this, position, angles );
}
bool sdk::c_base_entity::is_player( )
{
	static auto is_player_address = g_signatures[ "B0 ? C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 56" ].as< std::uintptr_t >( );
	using is_player_type          = bool( __thiscall* )( void* );

	return reinterpret_cast< is_player_type >( is_player_address )( this );
}
