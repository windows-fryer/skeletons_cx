
#ifndef WEDNESDAY_WTF_ANIMATIONS_HPP
#define WEDNESDAY_WTF_ANIMATIONS_HPP

#include "../../helpers/interfaces/interfaces.hpp"
#include <array>

namespace animations
{

	struct animation_data {
	public:
		bool needs_resolve = false;
		sdk::vector last_velocity{ };
	};

	struct impl {
	public:
		std::array< animation_data, 65 > animation_info{ };
		void on_create_move( );

		void on_update_clientside_anims( sdk::c_tf_player* entity, float& yaw, float& pitch );
	};

} // namespace animations

inline animations::impl g_animations;

#endif // WEDNESDAY_WTF_ANIMATIONS_HPP
