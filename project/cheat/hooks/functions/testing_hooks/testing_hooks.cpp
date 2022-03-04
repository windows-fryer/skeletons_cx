#include "testing_hooks.hpp"

// this looks interesting
int __fastcall hooks::testing_hooks::sub_10401C70_detour( void* _ecx, void* _edx_unused, int a3, int a4 )
{
	// void* a2;// get 2nd arg from esi (according to ida, this is probably bullshit)
	//__asm mov a2, esi;

	//	int result = hooks::sub_10401C70_hook.call_original( _ecx, _edx_unused, a3, a4 );
	//	return result;
	return 1;
}
