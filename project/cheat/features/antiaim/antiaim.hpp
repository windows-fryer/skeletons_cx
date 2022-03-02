
#ifndef SKELETONS_CX_ANTIAIM_HPP
#define SKELETONS_CX_ANTIAIM_HPP

#include "../../helpers/interfaces/interfaces.hpp"

namespace antiaim
{
	struct impl {
	public:
		sdk::qangle local_real_angle{ }; // sdk::matrix_3x4 local_real[ 128 ]{ };

		void fakelag( sdk::c_user_cmd* cmd, bool& send_packet );
		void do_180_sway( bool& send_packet ); // sway lee nigga thuggin

		// todo: create animfix.cpp or smth
		void update_fake( bool& send_packet );

	private:
	};

} // namespace antiaim

inline antiaim::impl g_antiaim;

#endif // SKELETONS_CX_ANTIAIM_HPP
