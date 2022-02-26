#ifndef SKELETONS_CX_LIFE_STATE_HPP
#define SKELETONS_CX_LIFE_STATE_HPP

namespace sdk
{

	enum life_state {
		LIFE_ALIVE = 0,
		LIFE_DYING,
		LIFE_DEAD,
		LIFE_RESPAWNABLE,
		LIFE_DISCARDBODY
	};

} // namespace sdk

#endif // SKELETONS_CX_LIFE_STATE_HPP
