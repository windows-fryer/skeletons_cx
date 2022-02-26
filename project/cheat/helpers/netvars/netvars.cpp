#include "netvars.hpp"

#include "../../helpers/interfaces/interfaces.hpp"

std::uint32_t netvar_manager::impl::get_offset( sdk::recv_table* table, const char* var )
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