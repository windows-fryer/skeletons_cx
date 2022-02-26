#ifndef SKELETONS_CX_MOVEMENT_HPP
#define SKELETONS_CX_MOVEMENT_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace movement
{

	struct impl {
	public:
		void move_fix( sdk::c_user_cmd* cmd, const sdk::qangle& old_angle );

	private:
	};
} // namespace movement

inline movement::impl g_movement;

#endif // SKELETONS_CX_MOVEMENT_HPP
