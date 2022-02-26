#ifndef SKELETONS_CX_INTERFACES_HPP
#define SKELETONS_CX_INTERFACES_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <windows.h>

#include "../../sdk/include.hpp"
#include "../snakeify.hpp"

namespace interfaces
{
	struct interface_node {
	public:
		void* ( *get )( );
		const char* name;
		interface_node* next;
	};

	struct impl {
	private:
		std::unordered_map< std::uint32_t, std::uintptr_t > interfaces;

		void find_interfaces( );
		std::uintptr_t jump_address( std::uintptr_t address );

	public:
		sdk::i_engine_client* engine_client;
		sdk::i_base_client_dll* base_client;
		sdk::i_client_entity_list* entity_list;

		void init( );
		void shutdown( );
	};
} // namespace interfaces

inline interfaces::impl g_interfaces;

#endif // SKELETONS_CX_INTERFACES_HPP
