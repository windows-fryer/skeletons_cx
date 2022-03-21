#ifndef SKELETONS_CX_ASSERTION_HPP
#define SKELETONS_CX_ASSERTION_HPP

#include <chrono>
#include <exception>
#include <string>
#include <thread>

#include "../../globals/snakeify.hpp"
#include "../console/console.hpp"

#define assert_block( id, func )                                                                                                                     \
	try {                                                                                                                                            \
		func;                                                                                                                                        \
	} catch ( std::exception & exception ) {                                                                                                         \
		assertion::log( std::format( "Assertion hit on {}", id ), exception );                                                                       \
	}

namespace assertion
{
	enum assertion_flags {
		assertion_log_console     = 1 << 0, // assertion in game
		assertion_log_messageboxa = 1 << 1, //
		assertion_log_dev_console = 1 << 2, //
		assertion_log_max         = 1 << 3  // unused
	};

	template< auto assertion_type = assertion_log_console >
	void log( std::string_view assertion_message, std::exception& exception )
	{
		if ( assertion_type & assertion_log_console ) {
			console::log( "[ASSERT] " );

			console::color::red( );
			console::log( "{} [{}]\n", assertion_message, exception.what( ) );
			console::color::white( );
		}
	}

} // namespace assertion

#endif // SKELETONS_CX_ASSERTION_HPP
