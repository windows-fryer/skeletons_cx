//
// Created by Liga on 2/23/2022.
//

#ifndef SKELETONS_CX_CHEAT_HPP
#define SKELETONS_CX_CHEAT_HPP

#include <Windows.h>
#include <iostream>

#include "features/menu/menu.hpp"
#include "globals/globals.hpp"
#include "hooks/hooks.hpp"

namespace cheat
{
	inline HINSTANCE module_handle;

	void init( );
	void shutdown( );
} // namespace cheat

#endif // WEDNESDAY_TF2_CHEAT_HPP
