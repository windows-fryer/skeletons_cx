#pragma once

#include "../../../../../globals/globals.hpp"
#include "../../../../../helpers/input/input.hpp"
#include "../../../../../helpers/renderer/renderer.hpp"

#include "objects/base_object.hpp"

namespace menu
{
	enum class group_position : int
	{
		GROUP_LEFT  = ( 1 << 0 ),
		GROUP_RIGHT = ( 1 << 1 ),
	};

	struct tab;

	struct group {
		group( tab* parent_tab, std::string name, int position, bool extended )
			: parent_tab( parent_tab ), name( name ), position( position ), extended( extended ){ };

		tab* parent_tab{ };

		std::string name{ };

		int position{ };

		bool extended{ };

		int cursor_position{ };

		int scroll_amount{ };
		int needed_scroll_amount{ };

		std::vector< menu::base_object* > objects{ };

		void draw( int& window_x, int& window_y, int& size_x, int& size_y, int current_index );
		void input( int& window_x, int& window_y, int& size_x, int& size_y, int current_index );
	};
} // namespace menu
