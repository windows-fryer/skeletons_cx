#include "fire_event_intern.hpp"
#include "../../../helpers/entity_list/entity_list.hpp"

bool hooks::fire_event_intern::fire_event_intern_detour( void* ecx, void* edx, sdk::i_game_event* event, bool server_only, bool client_only )
{
	if ( event->get_int( "achievement" ) == 0xCA7 || event->get_int( "achievement" ) == 0xCA8 ) {
		if ( auto player_index = event->get_int( "player" ) ) {
			if ( auto player_info = &g_entity_list.players[ player_index ] ) {
				player_info->bot = true;
			}
		}
	}

	return fire_event_intern_hook.call_original( ecx, edx, event, server_only, client_only );
}
