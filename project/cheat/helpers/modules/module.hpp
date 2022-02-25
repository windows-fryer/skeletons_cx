#ifndef SKELETONS_CX_MODULE_HPP
#define SKELETONS_CX_MODULE_HPP

#include <Windows.h>
#include <string>
#include "../../globals/snakeify.hpp"

struct game_module{
public:

	game_module( std::string_view module_name ) {
		module_handle = get_module_handle(module_name.data());

		// todo: add assertion
		if(!module_handle){

		}
	}

private:
	HMODULE module_handle;

};

#endif // SKELETONS_CX_MODULE_HPP
