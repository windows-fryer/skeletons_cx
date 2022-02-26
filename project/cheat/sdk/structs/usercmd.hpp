#ifndef SKELETONS_CX_USERCMD_HPP
#define SKELETONS_CX_USERCMD_HPP

#include "../structs/qangle.hpp";

struct user_cmd {
public:
	virtual ~user_cmd( ){ };
	int command_number;
	int tick_count;
	sdk::qangle view_angles;
	float forward_move;
	float side_move;
	float up_move;
	int buttons;
	std::uint8_t impulse;
	int weapon_select;
	int weapon_subtype;
	int random_seed;
	short mouse_dx;
	short mouse_dy;
	bool has_been_predicted;
};

#endif // SKELETONS_CX_USERCMD_HPP
