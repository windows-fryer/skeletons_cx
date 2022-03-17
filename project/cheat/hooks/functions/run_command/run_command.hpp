#ifndef SKELETONS_CX_RUN_COMMAND_HPP
#define SKELETONS_CX_RUN_COMMAND_HPP

#define NOMINMAX

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( run_command_hook, void( __fastcall )( void*, void*, sdk::c_base_player*, sdk::c_user_cmd*, void* ), void );

	struct run_command {
		static void __fastcall run_command_detour( void* ecx, void* edx, sdk::c_base_player* player, sdk::c_user_cmd* command, void* move_helper );

		static void init( )
		{
			run_command_hook.create( g_signatures[ "55 8B EC 51 53 56 8B F1 57 89 75 ? E8 ? ? ? ? 8B 7D" ], run_command_detour,
			                         "run_command_detour" );
		}

		static void shutdown( )
		{
			run_command_hook.disable( );
		}
	};
} // namespace hooks

#endif // SKELETONS_CX_RUN_COMMAND_HPP
