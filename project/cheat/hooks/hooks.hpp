#ifndef SKELETONS_CX_HOOKS_HPP
#define SKELETONS_CX_HOOKS_HPP

#include "../../dependencies/minhook/MinHook.h"
#include "../cheat.hpp"
#include "../helpers/vfunc/vfunc.hpp"

namespace hooks
{
	template< class T, class R >
	struct hook_helper {
	private:
		void* source;
		void* original;

	public:
		void create( auto source, auto destination, const char* name = "undefined" )
		{
			if ( MH_CreateHook( ( void* )source, ( void* )destination, &original ) != MH_OK ) {
				console::log( "[HOOKS] " );

				console::color::red( );
				console::log( "Failed to create hook [ {} ]\n", name );
				console::color::white( );

				return;
			}

			this->source = source;

			console::log( "[HOOKS] " );

			console::color::cyan( );
			console::log( "Created hook [ {} ]\n", name );
			console::color::white( );
		}

		void disable( )
		{
			MH_DisableHook( source );
		}

		template< typename... ARGS >
		R call_original( ARGS&&... arguments )
		{
			return ( R )( reinterpret_cast< T* >( original )( arguments... ) );
		}
	};

	struct impl {
	public:
		void init( );
		void shutdown( );
	};
} // namespace hooks

inline hooks::impl g_hooks;

#define CREATE_HOOK_HELPER( name, args, rtn ) inline hook_helper< args, rtn > name;

#endif // SKELETONS_CX_HOOKS_HPP
