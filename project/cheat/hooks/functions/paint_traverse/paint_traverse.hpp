#ifndef SKELETONS_CX_PAINT_TRAVERSE_HPP
#define SKELETONS_CX_PAINT_TRAVERSE_HPP

#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( paint_traverse_hook, void( __fastcall )( void*, void*, sdk::vpanel, bool, bool ), void );

	struct paint_traverse {
		static void __fastcall paint_traverse_detour( void* ecx, void* edx, sdk::vpanel panel, bool force_repaint, bool allow_force );

		static void init( )
		{
			paint_traverse_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.panel, 41 ), paint_traverse_detour,
			                            "paint_traverse_detour" );
		}

		static void shutdown( )
		{
			paint_traverse_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_PAINT_TRAVERSE_HPP
