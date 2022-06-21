#ifndef WEDNESDAY_WTF_I_BASE_CLIENT_STATE_HPP
#define WEDNESDAY_WTF_I_BASE_CLIENT_STATE_HPP

#include "../../helpers/signatures/signatures.hpp"
#include "i_net_channel.hpp"

namespace sdk
{
	struct c_clock_drift_mgr {
		enum {
			// this controls how much it smoothes out the samples from the server.
			num_clockdrift_samples = 16
		};

		// this holds how many ticks the client is ahead each time we get a server tick.
		// we average these together to get our estimate of how far ahead we are.
		float clock_offsets[ num_clockdrift_samples ];
		int cur_clock_offset;

		int server_tick; // last-received tick from the server.
		int client_tick; // the client's own tick counter (specifically, for interpolation during rendering).
	};

	struct i_base_client_state {
		PAD( 0x10 );
		i_net_channel* net_channel; // 0x10
		PAD( 0x140 );
		c_clock_drift_mgr clock_drift; // 0x154
		int delta_tick;                // 0x1a0
		PAD( 0x110 );
		int max_clients; // 0x2b4
		PAD( 0x4868 );
		float frame_time;           // 0x4b20
		int last_out_going_command; // 0x4b24
		int choked_commands;        // 0x4b28
		int last_command_ack;       // 0x4b2c

		//		static int delta_tick( )
		//		{
		//			return g_signatures[ "8B 15 ? ? ? ? 85 D2 8B 35" ].add( 0x2 ).get( 2 ).as< int >( );
		//		}
		//		static int last_command_ack( )
		//		{
		//			return g_signatures[ "FF 35 ? ? ? ? 8B 3E" ].add( 0x2 ).get( 2 ).as< int >( );
		//		}
		//		static int last_outgoing_command( )
		//		{
		//			return g_signatures[ "A1 ? ? ? ? 03 05" ].add( 0x2 ).get( 2 ).as< int >( );
		//		}
		//		static int choked_commands( )
		//		{
		//			return g_signatures[ "03 05 ? ? ? ? 8B 15" ].add( 0x2 ).get( 2 ).as< int >( );
		//		}
		//		static int relative_choked_commands( )
		//		{
		//			return choked_commands( ) - last_command_ack( );
		//		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_BASE_CLIENT_STATE_HPP
