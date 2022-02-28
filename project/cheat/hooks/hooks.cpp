#include "hooks.hpp"

#include "functions/create_move/create_move.hpp"
#include "functions/end_scene/end_scene.hpp"
#include "functions/frame_stage_notify/frame_stage_notify.hpp"
#include "functions/net_to/net_send_to.hpp"
#include "functions/override_view/override_view.hpp"
#include "functions/wndproc/wndproc.hpp"
void hooks::impl::init( )
{
	MH_Initialize( );

	create_move::init( );
	override_view::init( );
	frame_stage_notify::init( );
	wndproc::init( );
	end_scene::init( );
	net_send_to::init();


	MH_EnableHook( MH_ALL_HOOKS );
}

void hooks::impl::shutdown( )
{
	create_move::shutdown( );
	override_view::shutdown( );
	frame_stage_notify::shutdown( );
	wndproc::shutdown( );
	end_scene::shutdown( );

	MH_Uninitialize( );
}
