#include "update_clientside_anims.hpp"

void __fastcall hooks::update_clientside_anims::update_clientside_anims_detour( void* ecx, void* edx, float yaw, float pitch )
{
	{


	}

	return update_clientside_anims_hook.call_original( ecx, edx, yaw, pitch );
}
