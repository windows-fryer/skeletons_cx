#include "menu.hpp"

#include "window/tab/group/objects/checkbox.hpp"
#include "window/tab/group/objects/slider_float.hpp"
#include "window/tab/group/objects/slider_int.hpp"

#include "window/window.hpp"

static auto main_window = new menu::window{ };

bool menu::impl::init( )
{
	g_config.insert( "menu_color", config::option( sdk::color( 67, 0, 187 ) ) );

	g_config.insert( "menu_size_x", config::option( 400, 0, 0 ) );
	g_config.insert( "menu_size_y", config::option( 500, 0, 0 ) );

	g_config.insert( "bunny_hop", config::option( true ) );

	g_config.insert( "third_person", config::option( false ) );
	g_config.insert( "third_person_bind", config::option( 'V', 0, 0 ) );

	static auto misc_tab = new menu::tab{ main_window, std::string( "miscellaneous" ) };

	static auto misc_main_group = new menu::group{ misc_tab, "main", static_cast< int >( menu::group_position::GROUP_LEFT ), true };

	static auto thirdperson_misc_main_checkbox = new menu::check_box{ misc_main_group, fnv( "third_person" ), "third person" };
	thirdperson_misc_main_checkbox->add_keybind( fnv( "third_person_bind" ) );
	static auto bunnyhop_misc_main_checkbox = new menu::check_box{ misc_main_group, fnv( "bunny_hop" ), "bunny hop" };
	bunnyhop_misc_main_checkbox->add_color_picker( fnv( "menu_color" ) );

	misc_main_group->objects.push_back( bunnyhop_misc_main_checkbox );
	misc_main_group->objects.push_back( thirdperson_misc_main_checkbox );
	misc_tab->groups.push_back( misc_main_group );
	main_window->tabs.push_back( misc_tab );

	g_input.add_keybind( VK_INSERT, [ & ]( bool pressed ) {
		if ( pressed )
			menu_open = !menu_open;
	} );

	g_input.add_keybind( VK_HOME, [ & ]( bool pressed ) {
		if ( pressed )
			g_config.save( "test.json" );
	} );

	g_input.add_keybind( VK_END, [ & ]( bool pressed ) {
		if ( pressed )
			g_config.load( "test.json" );
	} );

	return true;
}

void menu::impl::draw( )
{
	if ( !menu_open )
		return;

	auto menu_size_x = g_config.find< int >( "menu_size_x" );
	auto menu_size_y = g_config.find< int >( "menu_size_y" );

	static int menu_position_x = g_globals.screen_size.x / 2 - menu_size_x / 2;
	static int menu_position_y = g_globals.screen_size.y / 2 - menu_size_y / 2;

	main_window->draw( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
	main_window->input( menu_position_x, menu_position_y, menu_size_x, menu_size_y );
}
