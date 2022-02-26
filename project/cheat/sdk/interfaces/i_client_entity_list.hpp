#ifndef SKELETONS_CX_I_CLIENT_ENTITY_LIST_HPP
#define SKELETONS_CX_I_CLIENT_ENTITY_LIST_HPP

namespace sdk
{
	struct i_client_networkable;
	struct i_client_unknown;
	struct c_base_handle;
	struct i_client_entity;

	struct i_client_entity_list {
	public:
		// get i_client_networkable interface for specified entity
		virtual i_client_networkable* get_client_networkable( int entnum )                      = 0;
		virtual i_client_networkable* get_client_networkable_from_handle( c_base_handle h_ent ) = 0;
		virtual i_client_unknown* get_client_unknown_from_handle( c_base_handle h_ent )         = 0;

		// note: this function is only a convenience wrapper.
		// it returns get_client_networkable( entnum )->get_i_client_entity().
		virtual i_client_entity* get_client_entity( int entnum )                      = 0;
		virtual i_client_entity* get_client_entity_from_handle( c_base_handle h_ent ) = 0;

		// returns number of entities currently in use
		virtual int number_of_entities( bool b_include_non_networkable ) = 0;

		// returns highest index actually used
		virtual int get_highest_entity_index( void ) = 0;

		// sizes entity list to specified size
		virtual void set_max_entities( int maxents ) = 0;
		virtual int get_max_entities( )              = 0;

		// for da culture!
		template< class T >
		T* get(const std::uint32_t& index){
			return (T*)get_client_entity(index);
		}
	};
} // namespace sdk

#endif // SKELETONS_CX_I_CLIENT_ENTITY_LIST_HPP
