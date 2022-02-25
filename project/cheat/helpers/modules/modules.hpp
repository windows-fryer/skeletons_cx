#ifndef SKELETONS_CX_MODULES_HPP
#define SKELETONS_CX_MODULES_HPP

#include "../../globals/snakeify.hpp"
#include <Windows.h>
#include <string>

namespace modules
{
	struct module {
	public:
		module( ) = default;

		module( std::string_view module_name )
		{
			module_handle     = get_module_handle( module_name.data( ) );
			this->module_name = module_name;

			// todo: add assertion
			// ASSERT( module_handle )
		}

		std::string get_module_name( )
		{
			return module_name; // copy is slow.. too bad!
		}

		HMODULE& unsafe_get_handle( )
		{
			return module_handle; // i have a feeling this will be called quite a bit so
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

} // namespace modules

inline modules::module client_dll{ }, engine_dll{ }, materialsystem_dll{ }, vguimatsurface_dll{ }, inputsystem_dll{ }, studiorender_dll{ },
	filesystem_stdio_dll{ }, server_dll{ };

#endif // SKELETONS_CX_MODULES_HPP
