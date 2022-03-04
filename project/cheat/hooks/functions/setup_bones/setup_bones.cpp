#include "setup_bones.hpp"

bool __fastcall hooks::setup_bones::setup_bones_detour( void* _ecx, void* _edx, int max_bones, int bone_mask, float current_time )
{
	return hooks::setup_bones_hook.call_original( _ecx, _edx, max_bones, bone_mask, current_time );
}
