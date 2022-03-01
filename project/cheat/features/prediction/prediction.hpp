
#ifndef SKELETONS_CX_PREDICTION_HPP
#define SKELETONS_CX_PREDICTION_HPP

#include "../../helpers/interfaces/interfaces.hpp"
#include "../movement/movement.hpp"

namespace prediction
{

	struct prediction_backup {
	public:
		bool is_in_prediction{ };
		bool first_time_running{ };

		float cur_time{ };
		float frame_time{ };
		int tick_count{ };
		int tick_base{ };
	};

	struct prediction_projectile_backup {
	public:
		sdk::vector origin{ };
		sdk::vector velocity{ };
		sdk::vector base_velocity{ };
		sdk::c_base_handle ground_entity{ };
		int flags{ };
		float duck_time{ };
		float duck_jump_time{ };
		bool ducked{ };
		bool ducking{ };
		bool in_duck_jump{ };
		float model_scale{ }; // useless
		float simulation_time{ };
	};

	struct impl {
	private:
		sdk::qangle velocity_to_angles( sdk::vector direction );

	public:
		prediction_backup pred_backup{ };
		prediction_projectile_backup pred_proj_backup{ };

		sdk::c_user_cmd fake_cmd{ };
		sdk::move_data_t fake_move_data{ };

		void set_prediction_random_seed( sdk::c_user_cmd* cmd );
		void set_prediction_player( sdk::c_tf_player* entity );

		void start( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity );

		void finish( sdk::c_user_cmd* cmd, sdk::c_tf_player* entity );

		void reset( );

		void projectile_backup( sdk::c_tf_player* entity );
		sdk::vector projectile_run( sdk::c_tf_player* entity );
		void projectile_restore( sdk::c_tf_player* entity );
	};

} // namespace prediction

inline prediction::impl g_prediction;

#endif // SKELETONS_CX_PREDICTION_HPP
