#ifndef SKELETONS_CX_CONSOLE_HPP
#define SKELETONS_CX_CONSOLE_HPP

#include <format>
#include <iostream>
#include <string>

namespace console
{
	void init( );
	void shutdown( );

	template< typename... ARGS >
	void log( std::string_view message, ARGS&&... arguments )
	{
		std::string_view formatted_string = std::vformat( message, std::make_format_args( arguments... ) );

		std::cout << formatted_string;
	}
} // namespace console

#endif // SKELETONS_CX_CONSOLE_HPP
