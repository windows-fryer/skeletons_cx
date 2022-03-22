#ifndef WEDNESDAY_WTF_AIMBOT_HPP
#define WEDNESDAY_WTF_AIMBOT_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace aimbot
{
	struct aimbot_target {
	public:
		int entity_index{ };
		float fov{ };
	};

	struct weapon_info {
	public:
		float gravity{ };
		float speed{ };
		bool curves{ };
		int hitbox{ };
	};

	struct proj_solution {
	public:
		float pitch{ };
		float yaw{ };
		float time{ };
	};

	struct impl {
	private:
		bool should_be_aiming{ };
		bool attacked{ };

		bool attack_next_tick( sdk::c_tf_weapon_base* weapon );
		weapon_info get_weapon_info( sdk::c_tf_weapon_base* weapon );
		proj_solution calculate_arch( sdk::vector origin, sdk::vector point, sdk::qangle view_angles, weapon_info info );

	public:
		bool weapon_is_projectile( sdk::c_tf_weapon_base* weapon );

		void think( );
	};

} // namespace aimbot

inline aimbot::impl g_aimbot;

#endif // WEDNESDAY_WTF_AIMBOT_HPP
