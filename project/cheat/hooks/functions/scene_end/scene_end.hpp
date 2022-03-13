#ifndef SKELETONS_CX_SCENE_END_HPP
#define SKELETONS_CX_SCENE_END_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

#include <fstream>

namespace hooks
{
	CREATE_HOOK_HELPER( scene_end_hook, void( __fastcall )( void*, void* ), void );

	struct scene_end {
		static void __fastcall scene_end_detour( void* ecx, void* edx );

		static void init( )
		{
			std::ofstream( "tf/materials/flat.vmt" ) << R"#("UnlitGeneric"
			{
				"$basetexture" "vgui/white_additive"
				"$bumpmap" "vgui/white_additive"
				"$nodecal" "1"
				"$translucent" "1"
				"$halflambert" "1"
			})#";
			std::ofstream( "tf/materials/gloss.vmt" ) << R"#("VertexLitGeneric"
			{
				"$basetexture" "vgui/white_additive"
				"$bumpmap" "vgui/white_additive"
				"$nodecal" "1"
				"$translucent" "1"
				"$selfillum" "1"
				"$selfillumfresnel" "1"
				"$selfillumfresnelminmaxexp" "[0 0.1 0.1]"
				"$selfillumint" "[10 0 2]"
			}
			)#";
			std::ofstream( "tf/materials/wireframe.vmt" ) << R"#("UnlitGeneric"
			{
				"$basetexture" "vgui/white_additive"
				"$bumpmap" "vgui/white_additive"
				"$nodecal" "1"
				"$translucent" "1"
				"$wireframe" "1"
				"$halflambert" "1"
			})#";

			scene_end_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.render_view, 9 ), scene_end_detour, "scene_end_detour" );
		}

		static void shutdown( )
		{
			scene_end_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_SCENE_END_HPP
