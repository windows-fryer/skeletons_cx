#include "hooks.hpp"
#include "functions/create_move/create_move.hpp"
#include "functions/frame_stage_notify/frame_stage_notify.hpp"
#include "functions/override_view/override_view.hpp"

void hooks::impl::init( )
{
	MH_Initialize( );

	create_move::init( );
	override_view::init( );
	frame_stage_notify::init( );

	MH_EnableHook( MH_ALL_HOOKS );
}

void hooks::impl::shutdown( )
{
	create_move::shutdown( );
	override_view::shutdown( );
	frame_stage_notify::init( );

	MH_Uninitialize( );
}
