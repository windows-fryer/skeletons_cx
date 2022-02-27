#include "input.hpp"

#include <windowsx.h>

void input::impl::think( UINT msg, WPARAM wparam, LPARAM lparam )
{
	std::uint8_t key_id   = 0;
	key_state_t key_state = key_state_t::KEY_UP;

	mouse.scroll_amt = 0;

	switch ( msg ) {
	case WM_KEYDOWN:
		key_id    = wparam;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_KEYUP:
		key_id    = wparam;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_LBUTTONDOWN:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_LBUTTONUP:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_LBUTTONDBLCLK:
		key_id    = VK_LBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_RBUTTONDOWN:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_RBUTTONUP:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_RBUTTONDBLCLK:
		key_id    = VK_RBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MBUTTONDOWN:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MBUTTONUP:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_MBUTTONDBLCLK:
		key_id    = VK_MBUTTON;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_XBUTTONDOWN:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_XBUTTONUP:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		key_state = key_state_t::KEY_UP;
		break;
	case WM_XBUTTONDBLCLK:
		key_id    = GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		key_state = key_state_t::KEY_DOWN;
		break;
	case WM_MOUSEMOVE:
		mouse.pos = sdk::vector( GET_X_LPARAM( lparam ), GET_Y_LPARAM( lparam ), 0 );
		break;
	case WM_MOUSEWHEEL:
		mouse.scroll_amt = -( GET_WHEEL_DELTA_WPARAM( wparam ) / ( WHEEL_DELTA / 4 ) );
		break;
	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		for ( auto& key : key_states )
			key.state = key_state_t::KEY_UP;
		break;
	default:
		break;
	}

	std::uint64_t time = GetTickCount64( );

	if ( key_id ) {
		if ( key_state == key_state_t::KEY_UP && key_states[ key_id ].state == key_state_t::KEY_DOWN )
			key_states[ key_id ] = { key_state_t::KEY_RELEASED, time };
		else
			key_states[ key_id ] = { key_state, time };

		for ( auto iterator = key_binds.begin( ); iterator != key_binds.end( ); ) {
			if ( iterator->awaiting_input ) {
				if ( key_id != VK_ESCAPE && key_id != VK_LBUTTON && key_id != VK_RBUTTON )
					iterator->poll_callback( key_id, key_state == key_state_t::KEY_UP ? false : key_state == key_state_t::KEY_DOWN );
				else
					iterator->callback( key_state == key_state_t::KEY_UP ? false : key_state == key_state_t::KEY_DOWN );
			}

			if ( iterator->virtual_key == key_id )
				iterator->callback( key_state == key_state_t::KEY_UP ? false : key_state == key_state_t::KEY_DOWN );

			iterator++;
		}
	}
}

void input::impl::add_keybind( std::uint8_t virtual_key, std::function< void( bool ) > callback )
{
	key_binds.push_back( { false, nullptr, virtual_key, callback } );
}

void input::impl::remove_keybind( std::uint8_t virtual_key )
{
	for ( auto iterator = key_binds.begin( ); iterator != key_binds.end( ); ) {
		if ( iterator->virtual_key == virtual_key )
			iterator = key_binds.erase( iterator );
		else
			iterator++;
	}
}

void input::impl::poll_keybind( std::function< void( std::uint8_t, bool ) > callback, std::function< void( bool ) > callback_fail )
{
	key_binds.push_back( { true, callback, 0x0, callback_fail } );
}

char* input::impl::key_to_char( std::uint8_t virtual_key )
{
	const char* key_names[] = {
		"Unknown",
		"LBUTTON",
		"RBUTTON",
		"CANCEL",
		"MBUTTON",
		"XBUTTON1",
		"XBUTTON2",
		"Unknown",
		"BACK",
		"TAB",
		"Unknown",
		"Unknown",
		"CLEAR",
		"RETURN",
		"Unknown",
		"Unknown",
		"SHIFT",
		"CONTROL",
		"MENU",
		"PAUSE",
		"CAPITAL",
		"KANA",
		"Unknown",
		"JUNJA",
		"FINAL",
		"KANJI",
		"Unknown",
		"ESCAPE",
		"CONVERT",
		"NONCONVERT",
		"ACCEPT",
		"MODECHANGE",
		"SPACE",
		"PRIOR",
		"NEXT",
		"END",
		"HOME",
		"LEFT",
		"UP",
		"RIGHT",
		"DOWN",
		"SELECT",
		"PRINT",
		"EXECUTE",
		"SNAPSHOT",
		"INSERT",
		"DELETE",
		"HELP",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"LWIN",
		"RWIN",
		"APPS",
		"Unknown",
		"SLEEP",
		"NUMPAD0",
		"NUMPAD1",
		"NUMPAD2",
		"NUMPAD3",
		"NUMPAD4",
		"NUMPAD5",
		"NUMPAD6",
		"NUMPAD7",
		"NUMPAD8",
		"NUMPAD9",
		"MULTIPLY",
		"ADD",
		"SEPARATOR",
		"SUBTRACT",
		"DECIMAL",
		"DIVIDE",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"NUMLOCK",
		"SCROLL",
		"OEM_NEC_EQUAL",
		"OEM_FJ_MASSHOU",
		"OEM_FJ_TOUROKU",
		"OEM_FJ_LOYA",
		"OEM_FJ_ROYA",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LSHIFT",
		"RSHIFT",
		"LCONTROL",
		"RCONTROL",
		"LMENU",
		"RMENU",
	};

	return const_cast< char* >( key_names[ virtual_key ] );
}