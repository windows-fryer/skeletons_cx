#include "signatures.hpp"
#include "../console/console.hpp"

void signatures::impl::init( )
{
	for ( auto& should_find : find ) {
		auto pattern = should_find.module.pattern_scan( should_find.pattern );

		if ( !pattern.m_address ) {
			console::log( "[SIGNATURES] " );

			console::color::red( );
			console::log( "Failed to find signature [ {} ]\n", should_find.pattern );
			console::color::white( );

			continue;
		}

		console::log( "[SIGNATURES] " );

		console::color::cyan( );
		console::log( "Found signature [ {} ]\n", should_find.pattern );
		console::color::white( );

		database.insert( std::make_pair( fnv( should_find.pattern ), pattern ) );
	}
}

void signatures::impl::shutdown( ) { }
