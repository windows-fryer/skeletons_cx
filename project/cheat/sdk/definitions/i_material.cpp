#include "../structs/i_material.hpp"
#include "../../helpers/vfunc/vfunc.hpp"

void sdk::i_material_var::set_vector( const sdk::vector& vec )
{
	using set_vector_type = void( __thiscall* )( void*, const sdk::vector& );

	reinterpret_cast< set_vector_type >( g_vfunc.get_virtual_function_index( this, 11 ) )( this, vec );
}

void sdk::i_material_var::set_component_value( float val, float comp )
{
	using set_vector_type = void( __thiscall* )( void*, float, float );

	reinterpret_cast< set_vector_type >( g_vfunc.get_virtual_function_index( this, 26 ) )( this, val, comp );
}
