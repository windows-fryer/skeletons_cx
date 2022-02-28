#pragma once

#include "../../globals/globals.hpp"
#include "../../helpers/input/input.hpp"
#include "../../helpers/renderer/renderer.hpp"
#include "config/config.hpp"

namespace menu
{
	struct impl {
		bool menu_open{ };

		bool init( );

		void draw( );
	};
}; // namespace menu

inline menu::impl g_menu;
