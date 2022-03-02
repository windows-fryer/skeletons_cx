#include "update_clientside_anims.hpp"
#include "../../../features/include.hpp"

void __fastcall hooks::update_clientside_anims::update_clientside_anims_detour( void* ecx, void* edx, float yaw, float pitch )
{
	if ( ecx == g_globals.local ) {
		yaw   = g_antiaim.local_real_angle.yaw;
		pitch = g_antiaim.local_real_angle.pitch;
	}

	return update_clientside_anims_hook.call_original( ecx, edx, yaw, pitch );
}
