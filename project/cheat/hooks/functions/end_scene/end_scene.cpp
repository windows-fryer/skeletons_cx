#include "end_scene.hpp"

long hooks::end_scene::end_scene_detour( IDirect3DDevice9* device )
{
	static auto multi_core_rendering = _ReturnAddress( );

	if ( multi_core_rendering != _ReturnAddress( ) )
		return end_scene_hook.call_original( device );

	g_render.setup_state( );

	g_render.render_line( 0, 0, 1920, 1080, { 255, 255, 255, 255 } );

	g_render.finish_state( );

	return end_scene_hook.call_original( device );
}
