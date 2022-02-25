#ifndef SKELETONS_CX_ASSERTION_HPP
#define SKELETONS_CX_ASSERTION_HPP

#include <string>


namespace assertion{

	enum assertion_flags{
		assertion_log_console = 0x1,		// assertion in game
		assertion_log_messageboxa,			//
		assertion_log_dev_console,			//
		assertion_log_max 					// unused
	};

	void assert(std::string_view assertion_message, unsigned char assertion_flag );


}



#endif // SKELETONS_CX_ASSERTION_HPP
