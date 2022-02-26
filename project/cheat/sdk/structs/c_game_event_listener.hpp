#ifndef SKELETONS_CX_C_GAME_EVENT_LISTENER_HPP
#define SKELETONS_CX_C_GAME_EVENT_LISTENER_HPP

#include "i_game_event.hpp"

namespace sdk
{
	struct c_game_event_listener {
	public:
		virtual ~c_game_event_listener( ){ };
		virtual void fire_game_event( i_game_event* event ) = 0;

	private:
		bool registered_for_events; // lol so useless -Liga (I hate padding)
	};

} // namespace sdk

#endif // SKELETONS_CX_C_GAME_EVENT_LISTENER_HPP
