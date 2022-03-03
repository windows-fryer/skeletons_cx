#include "animations.hpp"
#include "../../helpers/entity_list/entity_list.hpp"

void animations::impl::on_create_move( )
{
	for ( auto& player_info : g_entity_list.players ) {
		if ( auto entity = g_interfaces.entity_list->get< sdk::c_tf_player >( player_info.index ) ) {
			animation_data* anim_info = &animation_info[ player_info.index ];

			float delta_simtime = ( entity->simulation_time( ) - entity->get_old_simulation_time( ) );
			int ticks_choked    = time_to_ticks( delta_simtime );

			/* is choking packets */
			if ( ticks_choked > 1 ) {
				/* if theyre fake lagging, resolve em */
				anim_info->needs_resolve = true;
			}
		}
	}
}
void animations::impl::on_update_clientside_anims( sdk::c_tf_player* entity, float& yaw, float& pitch )
{
	/* get ticks choked by entity */
	int ticks_choked = time_to_ticks( ( entity->simulation_time( ) - entity->get_old_simulation_time( ) ) );

	sdk::qangle current_angle = entity->get_abs_angles( );

}