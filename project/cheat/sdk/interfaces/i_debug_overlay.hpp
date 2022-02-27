#ifndef SKELETONS_CX_I_DEBUG_OVERLAY_HPP
#define SKELETONS_CX_I_DEBUG_OVERLAY_HPP

#include "../structs/qangle.hpp"
#include "../structs/vector.hpp"

namespace sdk
{

	struct i_debug_overlay {
	public:
		virtual void add_entity_text_overlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format,
		                                      ... )                                                                                             = 0;
		virtual void add_box_overlay( const vector& origin, const vector& mins, const vector& max, qangle const& orientation, int r, int g, int b,
		                              int a, float duration )                                                                                   = 0;
		virtual void add_triangle_overlay( const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool no_depth_test,
		                                   float duration )                                                                                     = 0;
		virtual void add_line_overlay( const vector& origin, const vector& dest, int r, int g, int b, bool no_depth_test, float duration )      = 0;
		virtual void add_text_overlay( const vector& origin, float duration, const char* format, ... )                                          = 0;
		virtual void add_text_overlay( const vector& origin, int line_offset, float duration, const char* format, ... )                         = 0;
		virtual void add_screen_text_overlay( float fl_x_pos, float fl_y_pos, float fl_duration, int r, int g, int b, int a, const char* text ) = 0;
		virtual void add_swept_box_overlay( const vector& start, const vector& end, const vector& mins, const vector& max, const qangle& angles,
		                                    int r, int g, int b, int a, float fl_duration )                                                     = 0;
		virtual void add_grid_overlay( const vector& origin )                                                                                   = 0;
		virtual int screen_position( const vector& point, vector& screen )                                                                      = 0;
		virtual int screen_position( float fl_x_pos, float fl_y_pos, vector& screen )                                                           = 0;

		virtual void* get_first( void )          = 0;
		virtual void* get_next( void* current )  = 0;
		virtual void clear_dead_overlays( void ) = 0;
		virtual void clear_all_overlays( )       = 0;

		virtual void add_text_overlay_rgb( const vector& origin, int line_offset, float duration, float r, float g, float b, float alpha,
		                                   const char* format, ... ) = 0;
		virtual void add_text_overlay_rgb( const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char* format,
		                                   ... )                     = 0;

		virtual void add_line_overlay_alpha( const vector& origin, const vector& dest, int r, int g, int b, int a, bool no_depth_test,
		                                     float duration )             = 0;
		virtual void add_box_overlay2( const vector& origin, const vector& mins, const vector& max, qangle const& orientation, void* face_color,
		                               void* edge_color, float duration ) = 0;

	private:
		inline void add_text_overlay( const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) {
		} /* catch improper use of bad interface. needed because '0' duration can be resolved by compiler to null format string (i.e., compiles but
		     calls wrong function) */
	};
} // namespace sdk

#endif // SKELETONS_CX_I_DEBUG_OVERLAY_HPP
