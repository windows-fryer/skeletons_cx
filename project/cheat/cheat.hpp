//
// Created by Liga on 2/23/2022.
//

#ifndef SKELETONS_CX_CHEAT_HPP
#define SKELETONS_CX_CHEAT_HPP

#include <iostream>
#include <Windows.h>
#include "globals/globals.hpp"

namespace cheat
{
	struct impl {
	public:
		static void init( );
		static void shutdown( );
	};
} // namespace cheat

inline cheat::impl g_cheat;

#endif // WEDNESDAY_TF2_CHEAT_HPP
