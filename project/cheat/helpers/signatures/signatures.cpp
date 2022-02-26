#include "signatures.hpp"

void signatures::impl::init( )
{
	for ( auto& should_find : find )
		database.insert( std::make_pair( fnv( should_find.pattern ), should_find.module.pattern_scan( should_find.pattern ) ) );
}

void signatures::impl::shutdown( ) { }
