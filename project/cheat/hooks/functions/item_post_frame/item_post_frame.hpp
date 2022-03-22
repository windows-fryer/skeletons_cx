#ifndef WEDNESDAY_WTF_ITEM_POST_FRAME_HPP
#define WEDNESDAY_WTF_ITEM_POST_FRAME_HPP

#include "../../../globals/globals.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( item_post_frame_hook, void( __fastcall )( void*, void* ), void );

	struct item_post_frame {
		static void __fastcall item_post_frame_detour( void* ecx, void* edx );

		static void init( )
		{
			item_post_frame_hook.create( g_signatures[ "55 8B EC 83 EC ? 56 57 8B F9 8B 37" ], item_post_frame_detour, "item_post_frame_detour" );
		}

		static void shutdown( )
		{
			item_post_frame_hook.disable( );
		}
	};
} // namespace hooks

#endif // WEDNESDAY_WTF_ITEM_POST_FRAME_HPP
