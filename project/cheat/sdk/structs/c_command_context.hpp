#ifndef SKELETONS_CX_C_COMMAND_CONTEXT_HPP
#define SKELETONS_CX_C_COMMAND_CONTEXT_HPP

#include "c_user_cmd.hpp"

namespace sdk
{
	struct c_command_context {
	public:
		bool needs_processing;
		c_user_cmd command;
		int command_number;
	};
} // namespace sdk

#endif // SKELETONS_CX_C_COMMAND_CONTEXT_HPP
