

#ifndef SKELETONS_CX_NETVARS_HPP
#define SKELETONS_CX_NETVARS_HPP
#include "../../sdk/structs/client_class.hpp"
#include <cstdint>

namespace netvar_manager
{

	struct impl {
	public:
		recv_var_proxy_fn find_proxy_table( recv_table* table, const char* var, recv_var_proxy_fn function );
		recv_var_proxy_fn change_proxy( const char* table, const char* var, recv_var_proxy_fn function );
		std::uint32_t get_offset( recv_table* table, const char* var );
		std::uint32_t get_table( const char* table, const char* var );
	};
} // namespace netvar_manager

inline netvar_manager::impl g_netvar_manager;


#define NETVAR(name, type, table, var) inline type &name()\
{\
	static int offset = g_netvar_manager.get_table(table, var);\
	return *reinterpret_cast<type*>(reinterpret_cast<std::uint32_t>(this) + offset);\
}

#endif // SKELETONS_CX_NETVARS_HPP
