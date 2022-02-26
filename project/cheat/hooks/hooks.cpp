#include "hooks.hpp"
#include "functions/create_move/create_move.hpp"
#include "functions/render_view/render_view.hpp"

void hooks::impl::init( )
{
	MH_Initialize( );

	create_move::init( );
	override_view::init( );

	MH_EnableHook( MH_ALL_HOOKS );
}

void hooks::impl::shutdown( )
{
	create_move::shutdown( );

	MH_Uninitialize( );
}
