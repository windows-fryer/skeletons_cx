#ifndef SKELETONS_CX_ENTRY_HPP
#define SKELETONS_CX_ENTRY_HPP

#include "cheat/globals/globals.hpp"
#include "cheat/cheat.hpp"

#include <Windows.h>
#include <cstdint>
#include <iostream>


namespace entry
{
	struct impl {
	public:
		static void init( );
		static void shutdown( );
	};
} // namespace entry

inline entry::impl g_entry;

#endif // SKELETONS_CX_ENTRY_HPP
