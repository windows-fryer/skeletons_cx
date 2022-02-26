#include "netvars.hpp"

#include "../../helpers/interfaces/interfaces.hpp"

recv_var_proxy_fn netvar_manager::impl::find_proxy_table( recv_table* table, const char* var, recv_var_proxy_fn function )
{
	for ( int i = 0; i < table->m_n_props; i++ ) {
		auto cur_prop = table->props[ i ];

		if ( strstr( var, cur_prop.var_name ) ) {
			recv_var_proxy_fn old_proxy = cur_prop.m_proxy_fn;
			cur_prop.m_proxy_fn         = function;

			return old_proxy;
		}

		auto data_table = cur_prop.get_data_table( );

		if ( data_table ) {
			recv_var_proxy_fn found_table = find_proxy_table( data_table, var, function );

			if ( found_table )
				return found_table;
		}
	}

	return 0x0;
}

recv_var_proxy_fn netvar_manager::impl::change_proxy( const char* table, const char* var, recv_var_proxy_fn function )
{
	auto classes = g_interfaces.base_client->get_all_classes( );

	for ( auto current_table = classes; current_table; current_table = current_table->next ) {
		if ( strstr( table, current_table->network_name ) ) {
			return find_proxy_table( current_table->recv_table, var, function );
		}
	}

	return 0x0;
}

std::uint32_t netvar_manager::impl::get_offset( recv_table* table, const char* var )
{
	for ( int i = 0; i < table->m_n_props; i++ ) {
		auto cur_prop = table->props[ i ];

		if ( strstr( var, cur_prop.var_name ) )
			return cur_prop.get_offset( );

		auto data_table = cur_prop.get_data_table( );

		if ( data_table ) {
			std::uint32_t offset = get_offset( data_table, var );

			if ( offset )
				return offset + cur_prop.get_offset( );
		}
	}

	return 0x0;
}

std::uint32_t netvar_manager::impl::get_table( const char* table, const char* var )
{
	auto classes = g_interfaces.base_client->get_all_classes( );

	for ( auto cur_table = classes; cur_table; cur_table = cur_table->next ) {
		if ( strstr( table, cur_table->network_name ) )
			return get_offset( cur_table->recv_table, var );
	}

	return 0x0;
}