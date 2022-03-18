#include "slider_int.hpp"
#include "../../../window.hpp"
#include "../group.hpp"
#include <algorithm>

void menu::slider_int::draw( int& group_x, int& group_y, int& group_width, int& group_height )
{
	// ur mic is shit btw blanket

	auto menu_color = g_config.find< sdk::color >( "menu_color" );
	auto menu_font  = g_fonts[ "menu_font" ];

	auto font_size = g_render.render_text_size( option_name.c_str( ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	auto slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	auto slider_border_height = slider_y + 12;

	int option_min{ };
	int option_max{ };

	auto& option = g_config.find< int >( option_hash, option_min, option_max );
	auto negative_adjustment =
		( slider_border_width - slider_x ) * ( -( static_cast< float >( option_max ) / ( option_max - option_min ) ) + 1.f ) - 1;

	g_render.render_text( slider_x + font_size.y / 2, slider_y + 4, AL_VERTICAL_CENTER, FLAG_NONE, option_name.c_str( ), menu_font,
	                      sdk::color( 255, 255, 255 ) );

	g_render.render_text( slider_border_width, slider_y + 5, AL_HORIZONTAL_LEFT | AL_VERTICAL_CENTER, FLAG_NONE, std::to_string( option ).c_str( ),
	                      menu_font, sdk::color( 255, 255, 255 ) );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width = slider_distance * slider_fraction;

	auto old_viewport = g_render.get_viewport( );

	g_render.set_viewport(
		{ slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2 },
		{ static_cast< float >( slider_border_width - slider_x - 7 ) + 1.f, static_cast< float >( slider_border_height - slider_y ) + 1.f } );

	g_render.render_filled_rectangle( ( slider_x + font_size.y / 2 ) + negative_adjustment, slider_y + font_size.y / 2 + 2, slider_width,
	                                  slider_border_height - slider_y, menu_color );

	g_render.render_rectangle( slider_x + font_size.y / 2, slider_y + font_size.y / 2 + 2, slider_border_width - slider_x - 7,
	                           slider_border_height - slider_y, { 43, 43, 43 } );

	g_render.set_viewport( old_viewport );

	group_y += slider_border_height - slider_y + 20;

	auto viewport = g_render.get_viewport( );

	int distance = ( group_y + group_height ) - ( static_cast< int >( viewport.Y ) + group_height );

	parent_group->needed_scroll_amount = distance;
}

void menu::slider_int::input( int& group_x, int& group_y, int& group_width, int& group_height )
{
	auto mouse_x = g_input.mouse.pos.x;
	auto mouse_y = g_input.mouse.pos.y;

	auto menu_color = g_config.find< sdk::color >( "menu_color" );
	auto menu_font  = g_fonts[ "menu_font" ];

	auto font_size = g_render.render_text_size( option_name.c_str( ), menu_font );

	int slider_x = group_x + font_size.y / 2 - 5;
	int slider_y = group_y + font_size.y / 2 + 3;

	int slider_border_width  = slider_x + ( group_width / 1.5 - ( font_size.y / 2 - 5 ) );
	int slider_border_height = slider_y + 12;

	int option_min{ };
	int option_max{ };

	auto& option             = g_config.find< int >( option_hash, option_min, option_max );
	auto negative_adjustment = ( slider_border_width - slider_x ) * ( -( static_cast< float >( option_max ) / ( option_max - option_min ) ) + 1.f );

	slider_y += 5;

	auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 );
	auto slider_fraction = static_cast< float >( option ) / ( static_cast< float >( option_max ) - static_cast< float >( option_min ) );

	auto slider_width   = slider_distance * slider_fraction;
	auto& parent_window = parent_group->parent_tab->parent_window;

	if ( menu::window::inside_position(
			 { mouse_x, mouse_y }, { slider_x + static_cast< float >( font_size.y ) / 2, slider_y + static_cast< float >( font_size.y ) / 2 + 2 },
			 { static_cast< float >( slider_border_width - slider_x - 7 ), static_cast< float >( slider_border_height - slider_y ) } ) ||
	     ( parent_window->dragging && parent_window->dragged_object == option_hash ) ) {
		parent_group->parent_tab->parent_window->allowed_to_drag = false;

		auto slider_distance = ( slider_border_width ) - ( slider_x + font_size.y / 2 + negative_adjustment );
		auto slider_fraction = ( mouse_x - ( slider_x + font_size.y / 2 + negative_adjustment ) );

		float slider_width = slider_fraction / slider_distance;

		auto viewport = g_render.get_viewport( );

		if ( g_input.key_state< input::KEY_DOWN >( VK_LBUTTON ) ) {
			int distance = ( slider_y + static_cast< int >( font_size.y ) / 2 + 2 ) - static_cast< int >( viewport.Y );

			if ( distance < group_height && distance > 0 ) {
				parent_window->dragging       = true;
				parent_window->dragged_object = option_hash;

				option = static_cast< int >( std::clamp( static_cast< int >( option_max * slider_width ), static_cast< int >( option_min ),
				                                         static_cast< int >( option_max ) ) );
			}
		} else {
			parent_group->parent_tab->parent_window->dragging       = false;
			parent_group->parent_tab->parent_window->dragged_object = { };
		}
	}

	group_y += slider_border_height - slider_y + 20;
}

void menu::slider_int::color_picker_draw( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_int::color_picker_input( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_int::key_bind_draw( int& group_x, int& group_y, int& group_width, int& group_height ) { }

void menu::slider_int::key_bind_input( int& group_x, int& group_y, int& group_width, int& group_height ) { }
