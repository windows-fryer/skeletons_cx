
#ifndef SKELETONS_CX_CREATE_MOVE_HPP
#define SKELETONS_CX_CREATE_MOVE_HPP
#include "../../hooks.hpp"

namespace hooking
{

	CREATE_HOOK_HELPER( create_move_hook, bool( __fastcall* )( void*, void*, void*, float ), bool );

	struct create_move {
		static bool __stdcall create_move_detour( void*, void*, void* user_cmd, float samples );

		static void init( ) { }
		static void unload( ) { }
	};
} // namespace hooking

#endif // SKELETONS_CX_CREATE_MOVE_HPP
