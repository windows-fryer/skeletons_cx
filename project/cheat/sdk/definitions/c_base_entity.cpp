#include "../structs/c_base_entity.hpp"
#include "../../helpers/vfunc/vfunc.hpp"

int sdk::c_base_entity::max_health( )
{
	return reinterpret_cast< int( __thiscall* )( void* ) >( g_vfunc.get_virtual_function_index( this, 107 ) )( this );
}

sdk::matrix_3x4& sdk::c_base_entity::rgfl_coordinate_frame( )
{
	return *reinterpret_cast< matrix_3x4* >( reinterpret_cast< std::uintptr_t >( this ) + 0x334 );
}

void sdk::c_base_entity::set_abs_origin( sdk::vector& position )
{
	static auto set_abs_origin_address = g_signatures[ "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3" ].as< std::uintptr_t >( );
	using set_abs_origin_type          = void( __thiscall* )( void*, const sdk::vector& );

	return reinterpret_cast< set_abs_origin_type >( set_abs_origin_address )( this, position );
}

void sdk::c_base_entity::invalidate_bone_cache( )
{
	static auto invalidate_bone_cache_address = g_signatures[ "A1 ? ? ? ? 48 C7 81" ].as< std::uintptr_t >( );
	using invalidate_bone_cache_type          = void( __thiscall* )( void* );

	return reinterpret_cast< invalidate_bone_cache_type >( invalidate_bone_cache_address )( this );
}