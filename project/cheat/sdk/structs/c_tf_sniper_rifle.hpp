#ifndef SKELETONS_CX_C_TF_SNIPER_RIFLE_HPP
#define SKELETONS_CX_C_TF_SNIPER_RIFLE_HPP

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_sniper_rifle : public c_tf_weapon_base {
	public:
		NETVAR( charged_damage, float, "CTFSniperRifle", "m_flChargedDamage" );
	};
} // namespace sdk

#endif // SKELETONS_CX_C_TF_SNIPER_RIFLE_HPP
