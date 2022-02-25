#ifndef SKELETONS_CX_HOOKING_HPP
#define SKELETONS_CX_HOOKING_HPP

#include <iostream>

#include "../../../dependencies/minhook/MinHook.h"
#include "../console/console.hpp"

namespace hooking
{
	template< class T >
	struct hook_helper {
	private:
		void* source;
		void* original;

	public:
		hook_helper( auto source, auto destination, const char* name = "undefined" )
		{
			if ( MH_CreateHook( ( void* )source, ( void* )destination, &original ) != MH_OK )
				console::log( "Failed to create hook [{}]", name );


		}
	};

	struct impl {
	public:
		std::vector <
	};
} // namespace hooking

#endif // SKELETONS_CX_HOOKING_HPP
