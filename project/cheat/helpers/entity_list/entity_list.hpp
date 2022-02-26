#ifndef SKELETONS_CX_ENTITY_LIST_HPP
#define SKELETONS_CX_ENTITY_LIST_HPP

#include "../../globals/globals.hpp"

namespace entity_list
{
	struct weapon {
	public:
		int index;
	};

	struct player {
	public:
		int index;
	};

	struct building {
	public:
		int index;
	};

	struct impl {
	public:
		std::vector< player > players;
		std::vector< building > buildings;

		void update( );
	};
} // namespace entity_list

#endif // SKELETONS_CX_ENTITY_LIST_HPP
