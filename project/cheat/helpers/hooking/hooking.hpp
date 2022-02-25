#ifndef SKELETONS_CX_HOOKING_HPP
#define SKELETONS_CX_HOOKING_HPP

#include <iostream>

#include "../../../dependencies/minhook/MinHook.h"
#include "../console/console.hpp"

namespace hooking
{
	template< class T, class R >
	struct hook_helper {
	private:
		void* source;
		void* original;

	public:
		void create( auto source, auto destination, const char* name = "undefined" )
		{
			if ( MH_CreateHook( ( void* )source, ( void* )destination, &original ) != MH_OK )
				console::log( "Failed to create hook [{}]", name );

			if ( MH_EnableHook( ( void* )source ) != MH_OK )
				console::log( "Failed to enable hook [{}]", name );

			this->source = source;

			console::log( "Created hook [{}]", name );
		}

		void disable( )
		{
			MH_DisableHook( ( void* )source );
		}

		template< typename... ARGS >
		R call_original( ARGS&&... arguments )
		{
			return reinterpret_cast< T* >( original )( arguments... );
		}

		T* get_original( )
		{
			return reinterpret_cast< T* >( original );
		};
	};

	void init( );
	void shutdown( );
} // namespace hooking

#endif // SKELETONS_CX_HOOKING_HPP
