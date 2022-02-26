#include "create_move.hpp"

bool __stdcall hooking::create_move::create_move_detour( void* user_cmd, float samples )
{

	using original_function = bool(__thiscall*)(void*, float, void*);
	static auto original = reinterpret_cast<original_function>(hooking::create_move_hook.get_original());
	bool result =


}
