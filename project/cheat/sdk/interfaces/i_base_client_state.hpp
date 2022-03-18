#ifndef SKELETONS_CX_I_BASE_CLIENT_STATE_HPP
#define SKELETONS_CX_I_BASE_CLIENT_STATE_HPP

#include "../../helpers/signatures/signatures.hpp"
#include "i_net_channel.hpp"

namespace sdk
{
	struct i_base_client_state {
		static int delta_tick( )
		{
			return g_signatures[ "8B 15 ? ? ? ? 85 D2 8B 35" ].add( 0x1 ).get( 2 ).as< int >( );
		}
		static int last_command_ack( )
		{
			return g_signatures[ "FF 35 ? ? ? ? 8B 3E" ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int last_outgoing_command( )
		{
			return g_signatures[ "A1 ? ? ? ? 03 05" ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int choked_commands( )
		{
			return g_signatures[ "03 05 ? ? ? ? 8B 15" ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int relative_choked_commands( )
		{
			return choked_commands( ) - last_command_ack( );
		}
	};
} // namespace sdk

#endif // SKELETONS_CX_I_BASE_CLIENT_STATE_HPP
