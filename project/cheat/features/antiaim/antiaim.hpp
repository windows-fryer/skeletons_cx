
#ifndef SKELETONS_CX_ANTIAIM_HPP
#define SKELETONS_CX_ANTIAIM_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace antiaim
{
	struct impl {
	public:
		void fakelag( sdk::c_user_cmd* cmd, bool& send_packet );

	private:
	};

} // namespace antiaim

inline antiaim::impl g_antiaim;

#endif // SKELETONS_CX_ANTIAIM_HPP
