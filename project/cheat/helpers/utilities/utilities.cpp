#include "utilities.hpp"

sdk::vector utilities::world_to_screen( sdk::vector position )
{
	auto matrix = g_globals.view_matrix;
	float width = matrix[ 3 ][ 0 ] * position.x + matrix[ 3 ][ 1 ] * position.y + matrix[ 3 ][ 2 ] * position.z + matrix[ 3 ][ 3 ];

	if ( width < 0.001f )
		return sdk::vector( -1, -1 );

	float inverse = 1.f / width;

	sdk::vector screen;

	screen.x = ( matrix[ 0 ][ 0 ] * position.x + matrix[ 0 ][ 1 ] * position.y + matrix[ 0 ][ 2 ] * position.z + matrix[ 0 ][ 3 ] ) * inverse;
	screen.y = ( matrix[ 1 ][ 0 ] * position.x + matrix[ 1 ][ 1 ] * position.y + matrix[ 1 ][ 2 ] * position.z + matrix[ 1 ][ 3 ] ) * inverse;

	auto screen_size = g_globals.screen_size;

	screen.x = ( screen_size.x * 0.5f ) + ( screen.x * screen_size.x ) * 0.5f;
	screen.y = ( screen_size.y * 0.5f ) - ( screen.y * screen_size.y ) * 0.5f;

	return sdk::vector( static_cast< int >( screen.x ), static_cast< int >( screen.y ) );
}

sdk::vector utilities::world_to_screen( sdk::vector position, bool& on_screen )
{
	on_screen = true;

	const auto matrix = g_globals.view_matrix;
	// not really needed but prevents useless math to be done
	if ( !matrix.data ) {
		on_screen = false;
		return { };
	}

	float width = matrix[ 3 ][ 0 ] * position.x + matrix[ 3 ][ 1 ] * position.y + matrix[ 3 ][ 2 ] * position.z + matrix[ 3 ][ 3 ];

	if ( width < 0.001f ) {
		on_screen = false;

		return sdk::vector( -1, -1 );
	}

	float inverse = 1.f / width;

	sdk::vector screen;

	screen.x = ( matrix[ 0 ][ 0 ] * position.x + matrix[ 0 ][ 1 ] * position.y + matrix[ 0 ][ 2 ] * position.z + matrix[ 0 ][ 3 ] ) * inverse;
	screen.y = ( matrix[ 1 ][ 0 ] * position.x + matrix[ 1 ][ 1 ] * position.y + matrix[ 1 ][ 2 ] * position.z + matrix[ 1 ][ 3 ] ) * inverse;

	auto screen_size = g_globals.screen_size;

	screen.x = ( screen_size.x * 0.5f ) + ( screen.x * screen_size.x ) * 0.5f;
	screen.y = ( screen_size.y * 0.5f ) - ( screen.y * screen_size.y ) * 0.5f;

	return sdk::vector( static_cast< int >( screen.x ), static_cast< int >( screen.y ) );
}