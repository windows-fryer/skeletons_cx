#ifndef SKELETONS_CX_MODULE_HPP
#define SKELETONS_CX_MODULE_HPP

#include "../../globals/snakeify.hpp"
#include <Windows.h>
#include <string>

struct game_module {
public:
	game_module( std::string_view module_name )
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
	HMODULE module_handle;
	std::string module_name;
};

#endif // SKELETONS_CX_MODULE_HPP
