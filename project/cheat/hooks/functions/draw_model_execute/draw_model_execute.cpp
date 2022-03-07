#include "draw_model_execute.hpp"

void hooks::draw_model_execute::draw_model_execute_detour( void* ecx, void* edx, void* state, sdk::model_render_info& info,
                                                           sdk::matrix_3x4* custom_bone_to_world )
{
	static sdk::i_material* material_regular;
	static sdk::i_material* material_flat;

	if ( !material_flat || !material_regular ) {
		material_regular = g_interfaces.material_system->find_material( "gloss" );
		material_flat    = g_interfaces.material_system->find_material( "flat" );

		material_regular->increment_reference_count( );
		material_flat->increment_reference_count( );
	}

	draw_model_execute_hook.call_original( ecx, edx, state, info, custom_bone_to_world );

	auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( info.entity_index );

	if ( !entity )
		return;

	if ( entity->get_client_class( )->class_id != sdk::e_class_ids::ctfplayer )
		return;

	material_flat->set_material_var_flag( 1 << 15, true );
	material_flat->color_modulate( 99 / 255.f, 0 / 255.f, 114 / 255.f );

	g_interfaces.model_render->forced_material_override( material_flat );

	draw_model_execute_hook.call_original( ecx, edx, state, info, custom_bone_to_world );

	g_interfaces.model_render->forced_material_override( nullptr );
}
