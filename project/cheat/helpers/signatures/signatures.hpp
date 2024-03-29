#ifndef WEDNESDAY_WTF_SIGNATURES_HPP
#define WEDNESDAY_WTF_SIGNATURES_HPP

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
			{ "55 8B EC 83 EC ? 53 56 8B 35 ? ? ? ? 33 DB 57 33 FF 89 5D ? 89 7D ? 8B 46", g_engine_dll },
			{ "55 8B EC 83 EC ? 56 8B F1 E8 ? ? ? ? 3B F0", g_client_dll },
			{ "55 8B EC 81 EC ? ? ? ? 53 57 8B F9 8B 9F", g_client_dll },
			{ "55 8B EC 8B 55 ? 85 D2 7E ? A1", g_server_dll },
			{ "55 8B EC 81 EC ? ? ? ? 53 56 8B 35 ? ? ? ? 8B D9 33 C9 33 D2 89 4D EC 89 55 F0 8B 46 08", g_client_dll },
			{ "55 8B EC 81 EC ? ? ? ? 53 56 57 6A 01 68 ? ? ? ? 8B F9 68 ? ? ? ? 68 ? ? ? ? 8D 87 ? ? ? ? 50 8D 45 A0 "
			  "50 E8 ? ? ? ? 8B 0D ? ? ? ? 33 D2 33 F6 89 55 DC 89 75 E0 83 C4 18 89 55 E4",
			  g_server_dll },
			{ "8A 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 80 B9", g_engine_dll },
			{ "84 C0 75 ? 38 05 ? ? ? ? 75 ? A1", g_engine_dll },
			{ "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 83 EC ? 83 3D", g_engine_dll },
			{ "55 8B EC 83 EC 38 83 3D ? ? ? ? ?", g_engine_dll },
			{ "55 8B EC 56 8B F1 8D 8E ? ? ? ? E8 ? ? ? ? 85 C0 75", g_engine_dll },
			{ "8B 45 ? C7 45 ? ? ? ? ? 5F 5E 85 C0 74 ? 6A ? 50 E8 ? ? ? ? 83 C4 ? 8B E5 5D C3", g_engine_dll },
			{ "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? DD 1D", g_engine_dll },
			{ "55 8B EC 51 53 56 8B F1 57 89 75 ? E8 ? ? ? ? 8B 7D", g_client_dll },
			{ "55 8B EC 83 EC ? 56 57 8B F9 8B 37", g_client_dll },
			{ "F6 87 ? ? ? ? ? 74 ? C7 87 ? ? ? ? ? ? ? ? 83 BF", g_client_dll },
			{ "55 8B EC 51 80 B9 14 4B 00 00", g_engine_dll },
			{ "D9 43 ? DF F1", g_engine_dll },
			{ "55 8B EC 81 EC ? ? ? ? 8B 0D ? ? ? ? 33 D2 89 55 ? 89 55 ? 89 55 ? 8B 41", g_engine_dll },
			{ "55 8B EC 83 EC 34 53 8B 5D 08 57 8B F9 89 7D FC 85 DB", g_engine_dll },
			{ "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? C3", g_client_dll },
			{ "A1 ? ? ? ? 03 05", g_engine_dll },
			{ "03 05 ? ? ? ? 8B 15", g_engine_dll },
			{ "8B 15 ? ? ? ? 85 D2 8B 35", g_engine_dll },
			{ "FF 35 ? ? ? ? 8B 3E", g_engine_dll },
			{ "55 8B EC 53 56 8B 75 ? 8B CE 57 FF 75 ? E8", g_client_dll },
			{ "55 8B EC B8 88 20 00 00", g_engine_dll },
			{ "68 ? ? ? ? E8 ? ? ? ? 83 C4 08 5F 5E 5B 5D C3", g_engine_dll },
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

#endif // WEDNESDAY_WTF_SIGNATURES_HPP
