#include "scene_end.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"

void hooks::scene_end::scene_end_detour( void* ecx, void* edx )
{
	static sdk::i_material* material_texture;
	static sdk::i_material* material_flat;

	if ( !material_texture || !material_flat ) {
		auto material_texture_kv = new sdk::key_values( "VertexLitGeneric" );
		material_texture_kv->set_string( "$selfillum", "1" );
		material_texture_kv->set_string( "$selfillumfresnel", "1" );
		material_texture_kv->set_string( "$bumpmap", "vgui/white_additive" );
		material_texture_kv->set_string( "$basetexture", "vgui/white_additive" );
		material_texture_kv->set_string( "$selfillumfresnelminmaxexp", "[0.1 1 2]" );
		material_texture = g_interfaces.material_system->create_material( "material_texture", material_texture_kv );

		auto material_flat_kv = new sdk::key_values( "UnlitGeneric" );
		material_flat_kv->set_string( "$basetexture", "vgui/white_additive" );
		material_flat = g_interfaces.material_system->create_material( "material_flat", material_flat_kv );
	}

	for ( auto& player_info : g_entity_list.players ) {
		if ( player_info.valid ) {
			if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
				material_flat->set_material_var_flag( 1 << 15, true );

				g_interfaces.model_render->suppress_engine_lighting( true );

				auto config_color = g_config.find< sdk::color >( "menu_color" );
				auto old_blend    = g_interfaces.render_view->get_blend( );

				g_interfaces.render_view->set_color_modulation( config_color );

				g_interfaces.model_render->forced_material_override( material_flat );
				g_interfaces.render_view->set_blend( config_color.a / 255.f );

				entity->draw_model( 0x1 );

				g_interfaces.model_render->forced_material_override( nullptr );

				g_interfaces.render_view->set_color_modulation( 1.f, 1.f, 1.f );
				g_interfaces.render_view->set_blend( old_blend );

				g_interfaces.model_render->suppress_engine_lighting( false );
			}
		}
	}
}
