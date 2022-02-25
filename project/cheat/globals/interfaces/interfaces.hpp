#ifndef SKELETONS_CX_INTERFACES_HPP
#define SKELETONS_CX_INTERFACES_HPP

#include <iostream>
#include <unordered_map>

#include "../../sdk/include.hpp"

namespace interfaces
{
	struct impl {
	public:
		std::unordered_map< std::uint32_t, std::uintptr_t > interfaces;
	};
} // namespace interfaces

inline interfaces::impl g_interfaces;

#endif // SKELETONS_CX_INTERFACES_HPP
