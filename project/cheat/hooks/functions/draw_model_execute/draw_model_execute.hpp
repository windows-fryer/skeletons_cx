#ifndef SKELETONS_CX_DRAW_MODEL_EXECUTE_HPP
#define SKELETONS_CX_DRAW_MODEL_EXECUTE_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

#include <fstream>

namespace hooks
{
	CREATE_HOOK_HELPER( draw_model_execute_hook, void( __fastcall )( void*, void*, void*, sdk::model_render_info&, sdk::matrix_3x4* ), void );

	struct draw_model_execute {
		static void __fastcall draw_model_execute_detour( void* ecx, void* edx, void* state, sdk::model_render_info& info,
		                                                  sdk::matrix_3x4* custom_bone_to_world );

		static void init( )
		{
			draw_model_execute_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.model_render, 19 ), draw_model_execute_detour,
			                                "draw_model_execute_detour" );
		}

		static void shutdown( )
		{
			draw_model_execute_hook.disable( );
		}
	};
} // namespace hooks
#endif // SKELETONS_CX_DRAW_MODEL_EXECUTE_HPP
