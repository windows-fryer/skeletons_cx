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
			{ "A1 ? ? ? ? 50 8B 08 FF 51 0C", g_shaderapidx9_dll },
			{ "68 ? ? ? ? 50 50 FF 12", g_engine_dll },
			{ "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3", g_client_dll },
			{ "A1 ? ? ? ? 48 C7 81", g_client_dll },
			{ "FF 35 ? ? ? ? 50 8B 11", g_client_dll },
			{ "55 8B EC 8B 45 ? 85 C0 75 ? C7 05", g_client_dll },
			{ "83 3D ? ? ? ? ? 74 ? 6A ? 50", g_client_dll },
			{ "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3", g_client_dll },
			{ "53 56 8B 35 ? ? ? ? 8B D9 8B CE 8B 06", g_client_dll },
			{ "56 8B F1 8B 06 FF 90 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 8B CE", g_client_dll },
			{ "8B 0D ? ? ? ? 8B 46 08 68 ? ? ? ? 05 ? ? ? ? 8B 11 50", g_client_dll },
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
