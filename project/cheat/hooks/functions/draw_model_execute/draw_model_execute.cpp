#include "draw_model_execute.hpp"

void hooks::draw_model_execute::draw_model_execute_detour( void* ecx, void* edx, void* state, sdk::model_render_info& info,
                                                           sdk::matrix_3x4* custom_bone_to_world )
{
	draw_model_execute_hook.call_original( ecx, edx, state, info, custom_bone_to_world );
}
