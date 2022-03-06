#include "is_playing_back.hpp"

bool __fastcall hooks::is_playing_back::is_playing_back_detour( void* ecx, void* edx )
{
	if ( g_signatures[ "84 C0 75 ? 38 05 ? ? ? ? 75 ? A1" ] == _ReturnAddress( ) )
		return true;

	return is_playing_back_hook.call_original( ecx, edx );
}
