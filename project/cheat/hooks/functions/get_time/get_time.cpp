#include "get_time.hpp"

float hooks::get_time::get_time_detour( void* ecx, void* edx )
{
	if ( _ReturnAddress( ) == g_signatures[ "D9 43 ? DF F1" ] )
		return FLT_MAX;

	return get_time_hook.call_original( ecx, edx );
}
