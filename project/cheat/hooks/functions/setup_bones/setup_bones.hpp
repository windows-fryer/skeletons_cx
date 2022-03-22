#ifndef WEDNESDAY_WTF_SETUP_BONES_HPP
#define WEDNESDAY_WTF_SETUP_BONES_HPP
#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{

	// gay compiler passes real 2nd arg through esi so...
	CREATE_HOOK_HELPER( setup_bones_hook, bool( __fastcall )( void*, void*, int, int, float ), bool );

	struct setup_bones {
		static bool __fastcall setup_bones_detour( void* _ecx, void* _edx, int max_bones, int bone_mask, float current_timek );

		static void init( )
		{
			setup_bones_hook.create( g_signatures[ "55 8B EC 81 EC ? ? ? ? 53 56 8B 35 ? ? ? ? 8B D9 33 C9 33 D2 89 4D EC 89 55 F0 8B 46 08" ],
			                         setup_bones_detour, "setup_bones_detour" );
		}
	};

} // namespace hooks
#endif // WEDNESDAY_WTF_SETUP_BONES_HPP
