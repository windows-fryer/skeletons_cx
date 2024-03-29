#ifndef WEDNESDAY_WTF_ENTITY_LIST_HPP
#define WEDNESDAY_WTF_ENTITY_LIST_HPP

#include "../../globals/global_vars.hpp"
#include "../../globals/snakeify.hpp"

#include "../../helpers/console/console.hpp"
#include "../../helpers/input/input.hpp"
#include "../../helpers/interfaces/interfaces.hpp"
#include "../../helpers/modules/modules.hpp"
#include "../../helpers/renderer/renderer.hpp"
#include "../../helpers/signatures/signatures.hpp"

#include "../../sdk/include.hpp"

namespace entity_list
{
	struct weapon {
	public:
		int index;
	};

	struct dormant_info {
	public:
		sdk::vector last_position{ };

		sdk::vector vouchable_position{ };

		int vouchable_tick{ };
		int found_tick{ };

		bool valid{ };
	};

	struct player {
	public:
		std::string name{ };

		sdk::vector mins{ };
		sdk::vector maxs{ };

		sdk::matrix_3x4 rgfl{ };

		int index{ };

		bool valid{ };

		dormant_info dormant_info{ };

		bool bot{ };

		int condition{ };
		int condition_ex{ };
		int condition_ex2{ };
	};

	struct building {
	public:
		int index;
	};

	struct impl {
	public:
		std::array< player, 65 > players;
		std::array< building, 48 > buildings;

		void update( );
		void clear( );
	};
} // namespace entity_list

inline entity_list::impl g_entity_list;

#endif // WEDNESDAY_WTF_ENTITY_LIST_HPP
