#ifndef SKELETONS_CX_VISUALS_HPP
#define SKELETONS_CX_VISUALS_HPP

#include "../../globals/globals.hpp"
#include "../../helpers/entity_list/entity_list.hpp"
#include "../../helpers/utilities/utilities.hpp"

#include <deque>

namespace visuals
{
	// Welcome to the great wall of esp. I have designed this as a nice object oriented way to
	// Do esp or visuals. If you want to create a new object follow the esp_box struct exactly.
	// Make a render function, all helper functions must be private! If they use rgfl matrix or
	// Use any function that relies i_collidable update them in paint like I do with esp_box rgfl.
	// This is an issue with CS:GO and multicore rendering and I plan on having more than 2 FPS.

	enum class esp_location : int
	{
		LOCATION_TOP = 0,
		LOCATION_LEFT,
		LOCATION_BOTTOM,
		LOCATION_RIGHT
	};

	struct esp_text {
	public:
		void render( sdk::box box, float& offset_x, float& offset_y );

		std::string text{ };

		sdk::color color{ };

		esp_location location{ };

		LPD3DXFONT font{ };

		font_flags flags{ };
	};

	struct esp_title : public esp_text {
	public:
		void render( sdk::box box, float& offset_x, float& offset_y );
	};

	struct esp_bar : public esp_text {
	public:
		void render( sdk::box box, float& offset_x, float& offset_y );

		float width{ };

		sdk::color color_from{ };
		sdk::color color_to{ };

		float max{ };
		float min{ };
		float cur{ };
	};

	struct esp_box {
	private:
		sdk::box calculate_box( sdk::c_tf_player* player, bool& on_screen );

	public:
		void render( sdk::c_tf_player* owner );

		bool outline[ 2 ]{ }; // 0 = outside, 1 = inside.
		bool cornered{ };

		sdk::color color{ };

		bool draw{ };

		bool skeleton{ };
		bool backtrack{ };

		std::deque< esp_title > titles{ };
		std::deque< esp_text > texts{ };
		std::deque< esp_bar > bars{ };
	};

	struct esp_object {
	public:
		esp_object( ) = default;
		esp_object( sdk::c_tf_player* owner ) : owner( owner ){ };

		sdk::c_tf_player* owner{ };

		esp_box box{ };
	};

	struct impl {
	private:
		void update_object( esp_object& object );

	public:
		std::array< esp_object, 65 > esp_objects{ };

		void update( );
		void render( );
	};
} // namespace visuals

inline visuals::impl g_visuals;

#endif // SKELETONS_CX_VISUALS_HPP
