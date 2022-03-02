#ifndef SKELETONS_CX_MOVEMENT_HPP
#define SKELETONS_CX_MOVEMENT_HPP

#include "../../helpers/interfaces/interfaces.hpp"
#include "../prediction/prediction.hpp"
#include <array>

namespace movement
{

	struct impl {
	public:
		void bunny_hop( );
		void move_fix( sdk::c_user_cmd* cmd, const sdk::qangle& old_angle );
		void run_prediction( sdk::c_tf_player* player );

	private:
	};
} // namespace movement

inline movement::impl g_movement;

#endif // SKELETONS_CX_MOVEMENT_HPP
