#ifndef WEDNESDAY_WTF_MOVEMENT_HPP
#define WEDNESDAY_WTF_MOVEMENT_HPP

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

#endif // WEDNESDAY_WTF_MOVEMENT_HPP
