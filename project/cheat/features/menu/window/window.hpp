#pragma once

#include "../../../globals/globals.hpp"
#include "../../../helpers/input/input.hpp"
#include "../../../helpers/renderer/renderer.hpp"

#include "tab/tab.hpp"

namespace menu
{
	struct window {
		bool dragging{ };
		std::uint32_t dragged_object{ };

		bool resizing{ };
		bool allowed_to_drag{ };

		std::uint32_t selected_tab{ };

		std::uint32_t selected_color_picker{ };
		bool dragging_alpha_color_picker{ };
		bool dragging_hue_color_picker{ };
		bool dragging_picker_color_picker{ };

		int color_picker_x{ };
		int color_picker_y{ };

		sdk::color copied_color{ };

		std::vector< menu::tab* > tabs{ };

		static bool inside_position( sdk::vector mouse_position, sdk::vector window_position, sdk::vector window_size );

		void draw( int& window_x, int& window_y, int& size_x, int& size_y );
		void input( int& window_x, int& window_y, int& size_x, int& size_y );
	};
} // namespace menu
