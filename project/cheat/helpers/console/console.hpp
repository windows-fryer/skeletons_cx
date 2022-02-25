#ifndef SKELETONS_CX_CONSOLE_HPP
#define SKELETONS_CX_CONSOLE_HPP

#include <string>

namespace console
{

	struct impl {
	public:

		void init( );
		void shutdown( );
		constexpr void log( std::string_view message );

	};

} // namespace console

inline console::impl g_console;

#endif // SKELETONS_CX_CONSOLE_HPP
