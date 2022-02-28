#include "end_scene.hpp"
#include "../../../features/menu/menu.hpp"
#include "../../../features/visuals/visuals.hpp"
#include "../../../sdk/structs/c_view_setup.hpp"

long hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto multi_core_rendering = _ReturnAddress( );

	if ( multi_core_rendering != _ReturnAddress( ) )
		return end_scene_hook.call_original( device );

	g_globals.screen_size = { static_cast< float >( g_render.get_viewport( ).Width ), static_cast< float >( g_render.get_viewport( ).Height ) };

	g_render.setup_state( );

	g_visuals.render( );
	g_menu.draw( );

	g_render.finish_state( );

	return end_scene_hook.call_original( device );
}
