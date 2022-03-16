#ifndef SKELETONS_CX_CONSOLE_HPP
#define SKELETONS_CX_CONSOLE_HPP

#include <format>
#include <iostream>
#include <string>
#include <windows.h>

namespace console
{
	namespace color
	{
		void blue( );

		void red( );

		void green( );

		void yellow( );

		void white( );

		void cyan( );

		void purple( );

		void grey( );
	} // namespace color

	void init( );
	void shutdown( );

	inline FILE *con_out, *con_in;

	template< typename... ARGS >
	void log( std::string_view message, ARGS&&... arguments )
	{
		std::string formatted_string = std::vformat( message.data( ), std::make_format_args( arguments... ) );

		std::cout << formatted_string;
	}
} // namespace console

#endif // SKELETONS_CX_CONSOLE_HPP
