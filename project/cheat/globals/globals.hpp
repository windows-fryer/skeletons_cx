#ifndef SKELETONS_CX_GLOBALS_HPP
#define SKELETONS_CX_GLOBALS_HPP

#include <iostream>
#include <windows.h>

#include "snakeify.hpp"

#include "../helpers/console/console.hpp"
#include "../helpers/input/input.hpp"
#include "../helpers/interfaces/interfaces.hpp"
#include "../helpers/modules/modules.hpp"
#include "../helpers/renderer/renderer.hpp"
#include "../helpers/signatures/signatures.hpp"

#include "../sdk/include.hpp"

namespace globals
{
	struct impl {
	public:
		sdk::c_user_cmd* command;

		sdk::c_tf_player* local;
		sdk::c_tf_weapon_base* local_weapon;
	};
} // namespace globals

inline globals::impl g_globals;

#endif // SKELETONS_CX_GLOBALS_HPP
