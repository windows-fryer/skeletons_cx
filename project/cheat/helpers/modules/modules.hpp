#ifndef WEDNESDAY_WTF_MODULES_HPP
#define WEDNESDAY_WTF_MODULES_HPP

#include "../../globals/snakeify.hpp"
#include "../patternscan/patternscan.hpp"

#include <Windows.h>
#include <string>

namespace modules
{
	struct module {
	public:
		module( ) = default;

		module( std::string_view module_name )
		{
			this->module_name = module_name;

			do {
				module_handle = get_module_handle( module_name.data( ) );
			} while ( !module_handle );
		}

		patternscan::address pattern_scan( std::string_view sig )
		{
			const auto module_address = reinterpret_cast< std::uint8_t* >( module_handle );
			const auto dos_header     = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
			const auto nt_headers     = reinterpret_cast< PIMAGE_NT_HEADERS >( module_address + dos_header->e_lfanew );

			return g_patternscan.find_pattern( module_address, nt_headers->OptionalHeader.SizeOfImage, sig.data( ) );
		}
		std::string get_module_name( )
		{
			return module_name;
		}

		HMODULE& unsafe_get_handle( )
		{
			return module_handle;
		}

		HMODULE get_handle( )
		{
			return module_handle;
		}

	private:
		HMODULE module_handle{ };
		std::string module_name{ };
	};

	void init( );
	void shutdown( );

} // namespace modules

inline modules::module g_client_dll{ }, g_engine_dll{ }, g_materialsystem_dll{ }, g_vguimatsurface_dll{ }, g_inputsystem_dll{ },
	g_studiorender_dll{ }, g_filesystem_stdio_dll{ }, g_server_dll{ }, g_shaderapidx9_dll{ };

#endif // WEDNESDAY_WTF_MODULES_HPP
