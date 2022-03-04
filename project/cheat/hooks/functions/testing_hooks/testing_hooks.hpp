
#ifndef SKELETONS_CX_TESTING_HOOKS_HPP
#define SKELETONS_CX_TESTING_HOOKS_HPP
#include "../../../globals/globals.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"
#include "../../../sdk/enums/client_frame_stage.hpp"
#include "../../hooks.hpp"

namespace hooks
{

	// gay compiler passes real 2nd arg through esi so...
	CREATE_HOOK_HELPER( sub_10401C70_hook, int( __fastcall )( void*, void*, int, int ), void );

	struct testing_hooks {
		static int __fastcall sub_10401C70_detour( void* _ecx, void* _edx_unused, int a3, int a4 );

		static void init( )
		{
			return;
			
			sub_10401C70_hook.create( g_signatures[ "55 8B EC 53 57 8B D9 E8 ? ? ? ? 8B 7D 08 84 C0 74 2A 8B 0D ? ? ? ? 8B 01 8B 40 3C FF D0 84 C0 "
			                                        "75 19 8B 0D ? ? ? ? 8B 01 8B 40 44 FF D0 84 C0 74 08 8D 47 E1 83 F8 08 77 25 56 8B 35 ? ? ? ?" ],
			                          sub_10401C70_detour, "sub_10401C70_detour" );
		}
	};

} // namespace hooks

#endif // SKELETONS_CX_TESTING_HOOKS_HPP
