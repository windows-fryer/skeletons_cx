#ifndef WEDNESDAY_WTF_LAGCOMP_HPP
#define WEDNESDAY_WTF_LAGCOMP_HPP

#define NOMINMAX

#include <iostream>
#include <windows.h>

#include "../../globals/snakeify.hpp"

#include "../../helpers/console/console.hpp"
#include "../../helpers/entity_list/entity_list.hpp"
#include "../../helpers/input/input.hpp"
#include "../../helpers/interfaces/interfaces.hpp"
#include "../../helpers/modules/modules.hpp"
#include "../../helpers/renderer/renderer.hpp"
#include "../../helpers/signatures/signatures.hpp"

#include "../../sdk/include.hpp"

namespace lagcomp
{
	struct record {
	public:
		record( ) = default;

		bool valid;
		float simulation_time;

		sdk::vector abs_origin;
		sdk::vector eye_position;

		sdk::c_tf_player* player;

		sdk::matrix_3x4 bone_matrix[ 128 ];
	};

	struct impl {
	private:
		// You should kill yourself NOW!
		// [ 1-64 ] is the range of possible player indexes.
		std::array< int, 65 > heap_iterator;
		float lerp_time( );
		bool is_valid( record heap_record );

	public:
		std::array< record*, 65 > heap_records;

		void update( );
		void cleanup( );

		void backtrack_player( record* heap_record );
		void backtrack_player( sdk::c_tf_player* player );
	};
} // namespace lagcomp

inline lagcomp::impl g_lagcomp;

#endif // WEDNESDAY_WTF_LAGCOMP_HPP
