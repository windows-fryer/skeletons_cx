#ifndef SKELETONS_CX_GLOBALS_HPP
#define SKELETONS_CX_GLOBALS_HPP

#include "snakeify.hpp"

#include "../helpers/console/console.hpp"
#include "../helpers/interfaces/interfaces.hpp"
#include "../helpers/modules/modules.hpp"
#include "../helpers/signatures/signatures.hpp"

#include "../sdk/include.hpp"

namespace globals
{
	struct impl {
	public:
		sdk::c_user_cmd* command;
	};
} // namespace globals

inline globals::impl g_globals;

#endif // SKELETONS_CX_GLOBALS_HPP
