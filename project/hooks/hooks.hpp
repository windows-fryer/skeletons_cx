#ifndef SKELETONS_CX_HOOKS_HPP
#define SKELETONS_CX_HOOKS_HPP

#include "../cheat/cheat.hpp"
#include "../cheat/helpers/hooking/hooking.hpp"

namespace hooking
{

	struct impl {
	public:
		void init( );
		void shutdown( );
	};
} // namespace hooking

inline hooks::impl g_hooks;

#endif // SKELETONS_CX_HOOKS_HPP
