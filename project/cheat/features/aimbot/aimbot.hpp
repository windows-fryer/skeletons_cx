#ifndef SKELETONS_CX_AIMBOT_HPP
#define SKELETONS_CX_AIMBOT_HPP

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
		sdk::vector offset{ };
	};

	struct impl {
	private:
		weapon_info get_weapon_info( sdk::c_tf_weapon_base* weapon );

	public:
		bool weapon_is_projectile( sdk::c_tf_weapon_base* weapon );

		void think( );
	};

} // namespace aimbot

inline aimbot::impl g_aimbot;

#endif // SKELETONS_CX_AIMBOT_HPP
