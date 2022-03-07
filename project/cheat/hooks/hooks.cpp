#include "hooks.hpp"

#include "functions/create_move/create_move.hpp"
#include "functions/draw_model_execute/draw_model_execute.hpp"
#include "functions/end_scene/end_scene.hpp"
#include "functions/enumerate_leaves_in_box/enumerate_leaves_in_box.hpp"
#include "functions/frame_stage_notify/frame_stage_notify.hpp"
#include "functions/is_playing_back/is_playing_back.hpp"
#include "functions/net_to/net_send_to.hpp"
#include "functions/override_view/override_view.hpp"
#include "functions/paint_traverse/paint_traverse.hpp"
#include "functions/setup_bones/setup_bones.hpp"
#include "functions/testing_hooks/testing_hooks.hpp"
#include "functions/update_clientside_anims/update_clientside_anims.hpp"
#include "functions/wndproc/wndproc.hpp"

void hooks::impl::init( )
{
	MH_Initialize( );

	create_move::init( );
	override_view::init( );
	frame_stage_notify::init( );
	wndproc::init( );
	end_scene::init( );
	net_send_to::init( );
	paint_traverse::init( );
	update_clientside_anims::init( );
	//	setup_bones::init( );
	is_playing_back::init( );
	enumerate_leaves_in_box::init( );
	draw_model_execute::init( );
	MH_EnableHook( MH_ALL_HOOKS );
}

void hooks::impl::shutdown( )
{
	// only do this if the hook requires specific shutdown shit!
	wndproc::shutdown( );

	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}
