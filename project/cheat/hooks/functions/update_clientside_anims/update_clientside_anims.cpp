#include "update_clientside_anims.hpp"
#include "../../../features/include.hpp"

void __fastcall hooks::update_clientside_anims::update_clientside_anims_detour( void* _ecx, void* _edx, float yaw, float pitch )
{
	auto entity = reinterpret_cast< sdk::c_tf_player* >( _ecx );

	if ( !g_globals.local || !g_globals.local->is_alive( ) )
		return update_clientside_anims_hook.call_original( _ecx, _edx, yaw, pitch );

	return update_clientside_anims_hook.call_original( _ecx, _edx, yaw, pitch );
}
