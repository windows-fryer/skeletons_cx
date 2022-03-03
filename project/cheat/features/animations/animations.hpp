
#ifndef SKELETONS_CX_ANIMATIONS_HPP
#define SKELETONS_CX_ANIMATIONS_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace animations
{

	struct impl {
	public:
		void on_update_clientside_anims( sdk::c_tf_player* entity, float& yaw, float& pitch );
	};

} // namespace animations

inline animations::impl g_animations;

#endif // SKELETONS_CX_ANIMATIONS_HPP
