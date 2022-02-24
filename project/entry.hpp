#ifndef WEDNESDAY_TF2_ENTRY_HPP
#define WEDNESDAY_TF2_ENTRY_HPP

#include "cheat/globals/globals.hpp"
#include "cheat/helpers/cheat.hpp"

#include <cstdint>
#include <iostream>
#include <windows.h>

namespace entry
{
	struct impl {
	public:
		static void init( );
		static void shutdown( );
	};
} // namespace entry

inline entry::impl g_entry;

#endif // WEDNESDAY_TF2_ENTRY_HPP
