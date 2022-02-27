
#ifndef SKELETONS_CX_PREDICTION_HPP
#define SKELETONS_CX_PREDICTION_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace prediction
{

	struct prediction_backup {
	public:
		float cur_time{ };
		float frame_time{ };
		int tick_count{ };
		int tick_base{ };
	};

	struct impl {
	public:
		prediction_backup pred_backup{ };

		void set_prediction_random_seed( sdk::c_user_cmd* cmd );
		void set_prediction_player( sdk::c_tf_player* entity );

		void start( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity );

		void finish( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity );

		void reset();
	};

} // namespace prediction

inline prediction::impl g_prediction;

#endif // SKELETONS_CX_PREDICTION_HPP
