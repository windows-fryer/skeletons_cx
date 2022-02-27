#include "../structs/c_base_player.hpp"
#include "../../helpers/interfaces/interfaces.hpp"
#include "../../helpers/modules/modules.hpp"
#include "../structs/player_info.hpp"

std::string sdk::c_base_player::name( )
{
	if ( sdk::player_info info{ }; g_interfaces.engine_client->get_player_info( this->entindex( ), &info ) )
		return { info.name };
	return { };
}