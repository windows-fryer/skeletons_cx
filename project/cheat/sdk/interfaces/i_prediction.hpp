#ifndef SKELETONS_CX_I_PREDICTION_HPP
#define SKELETONS_CX_I_PREDICTION_HPP
#include "../structs/c_user_cmd.hpp"
#include "../structs/vector.hpp"

#include <cstdint>
namespace sdk
{
	struct c_base_player;

	struct move_data_t {
	public:
		bool first_run_of_functions : 1;
		bool game_code_moved_player : 1;
		bool no_air_control         : 1;
		uint32_t player_handle;
		int impulse_command;
		vector view_angles;
		vector abs_view_angles;
		int buttons;
		int old_buttons;
		float forward_move;
		float side_move;
		float up_move;
		float max_speed;
		float client_max_speed;
		vector velocity;
		vector trailing_velocity;
		float trailing_velocity_time;
		vector angles;
		vector old_angles;
		float out_step_height;
		vector wish_velocity;
		vector jump_velocity;
		vector constraint_center;
		float constraint_radius;
		float constraint_width;
		float constraint_speed_factor;
		bool constraint_past_radius;

	private:
		vector vec_abs_origin;
	};

	class i_prediction
	{
	public:
		virtual ~i_prediction( ){ };
		virtual void initialize( void ) = 0;
		virtual void shutdown( void )   = 0;

		virtual void update( int start_frame, bool valid_frame, int incoming_ack, int outgoing_command )                      = 0;
		virtual void pre_entity_packet_recieved( int commands_ack, int current_world_update_packet )                          = 0;
		virtual void post_entity_packet_recieved( void )                                                                      = 0;
		virtual void post_network_data_recieved( int commands_ack )                                                           = 0;
		virtual void on_recieve_uncompressed_packet( void )                                                                   = 0;
		virtual void get_view_origin( vector& origin )                                                                        = 0;
		virtual void set_view_origin( vector& origin )                                                                        = 0;
		virtual void get_view_angles( qangle& angles )                                                                        = 0;
		virtual void set_view_angles( qangle& angles )                                                                        = 0;
		virtual void get_local_view_angles( qangle& angles )                                                                  = 0;
		virtual void set_local_view_angles( qangle& angles )                                                                  = 0;
		virtual bool get_is_in_prediction( void ) const                                                                       = 0;
		virtual bool get_is_first_time_predicted( void ) const                                                                = 0;
		virtual int get_last_ack_command_number( void ) const                                                                 = 0;
		virtual int get_incoming_packet_number( void ) const                                                                  = 0;
		virtual void check_moving_ground( sdk::c_base_player* player, double frame_time )                                     = 0;
		virtual void run_command( sdk::c_base_player* player, c_user_cmd* cmd, i_move_helper* move_helper )                   = 0;
		virtual void setup_move( sdk::c_base_player* player, c_user_cmd* cmd, i_move_helper* move_helper, move_data_t* data ) = 0;
		virtual void finish_move( sdk::c_base_player* player, c_user_cmd* cmd, move_data_t* data )                            = 0;

		std::int32_t& predicted_commands( )
		{
			return *reinterpret_cast< std::int32_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x1C );
		}

		std::int32_t& previous_start_frame( )
		{
			return *reinterpret_cast< std::int32_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0xC );
		}

		std::int32_t& server_commands_acknowledged( )
		{
			return *reinterpret_cast< std::int32_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x20 );
		}

		char epic_bytes1[ 8 ]{ };
		bool is_in_prediction;
		bool old_cl_predict_value;
		bool engine_paused;
		char epic_bytes2[ 13 ]{ };
		bool is_first_time_predicted;
	};
} // namespace sdk

#endif // SKELETONS_CX_I_PREDICTION_HPP
