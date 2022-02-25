#ifndef SKELETONS_CX_MODULE_HPP
#define SKELETONS_CX_MODULE_HPP

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
		HMODULE module_handle   = 0;
		std::string module_name = "";
	};

	inline module client_dll{ }, engine_dll{ }, materialsystem_dll{ }, vguimatsurface_dll{ }, inputsystem_dll{ }, studiorender_dll{ },
		filesystem_stdio_dll{ }, server_dll{ };

	void init( )
	{
		client_dll           = module( "client.dll" );
		engine_dll           = module( "engine.dll" );
		materialsystem_dll   = module( "materialsystem.dll" );
		vguimatsurface_dll   = module( "vguimatsurface.dll" );
		inputsystem_dll      = module( "inputsystem.dll" );
		studiorender_dll     = module( "studiorender.dll" );
		filesystem_stdio_dll = module( "filesystem_stdio.dll" );
		server_dll           = module( "server.dll" );
	};

} // namespace modules

#endif // SKELETONS_CX_MODULE_HPP
