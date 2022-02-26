#ifndef SKELETONS_CX_SIGNATURES_HPP
#define SKELETONS_CX_SIGNATURES_HPP

#include <unordered_map>
#include <vector>

#include "../../../dependencies/fnv/fnv.hpp"
#include "../../globals/snakeify.hpp"
#include "../modules/modules.hpp"
#include "../patternscan/patternscan.hpp"

namespace signatures
{
	struct signature {
	public:
		const char* pattern;
		modules::module& module;
	};

	struct impl {
	private:
		std::vector< signature > find = {
			{ "8B 0D ? ? ? ? FF 75 ? D9 45 ? 51 8B 01 D9 1C ? FF 75", g_client_dll },
			{ "B0 ? C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 56", g_client_dll },
			{ "8B 0D ? ? ? ? 8B 02 D9 05", g_client_dll },
		};

	public:
		std::unordered_map< std::uint32_t, patternscan::address > database{ };

		patternscan::address operator[]( const char* pattern )
		{
			return database[ fnv( pattern ) ];
		}

		patternscan::address operator[]( std::uint32_t pattern )
		{
			return database[ pattern ];
		}

		void init( );
		void shutdown( );
	};
} // namespace signatures

inline signatures::impl g_signatures;

#endif // SKELETONS_CX_SIGNATURES_HPP
