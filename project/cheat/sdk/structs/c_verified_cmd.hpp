#ifndef SKELETONS_CX_C_VERIFIED_CMD_HPP
#define SKELETONS_CX_C_VERIFIED_CMD_HPP

#include "c_user_cmd.hpp"

namespace sdk
{
	struct c_verified_cmd {
	public:
		c_user_cmd cmd;
		CRC32_t crc;
	};
} // namespace sdk

#endif // SKELETONS_CX_C_VERIFIED_CMD_HPP
