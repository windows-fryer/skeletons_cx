#include "enumerate_leaves_in_box.hpp"

bool hooks::enumerate_leaves_in_box::enumerate_leaves_in_box_detour( void* ecx, void* edx, sdk::vector& mins, sdk::vector& maxs, void* enumerator,
                                                                     int context )
{
	//	mins = { -16384.f, -16384.f, -16384.f };
	//	maxs = { 16384.f, 16384.f, 16384.f };

	for ( auto& entity_info : g_entity_list.players ) {
		if ( !entity_info.index )
			continue;

		auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( entity_info.index );

		if ( !entity )
			continue;

		auto info = g_interfaces.leaf_system->get_info_by_handle( entity->render_handle( ) );

		if ( !info )
			continue;

		info->flags        = 16 | 1;
		info->render_group = 7;
	}

	return enumerate_leaves_in_box_hook.call_original( ecx, edx, mins, maxs, enumerator, context );
}
