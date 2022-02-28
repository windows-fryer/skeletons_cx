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

	struct impl {
	public:
		void think( );
	};

} // namespace aimbot

inline aimbot::impl g_aimbot;

#endif // SKELETONS_CX_AIMBOT_HPP
