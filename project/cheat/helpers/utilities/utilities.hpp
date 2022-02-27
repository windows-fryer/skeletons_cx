#ifndef SKELETONS_CX_UTILITIES_HPP
#define SKELETONS_CX_UTILITIES_HPP

#include "../../globals/globals.hpp"
#include "../../sdk/structs/vector.hpp"

namespace utilities
{
	sdk::vector world_to_screen( sdk::vector position );
	sdk::vector world_to_screen( sdk::vector position, bool& on_screen );
} // namespace utilities

#endif // SKELETONS_CX_UTILITIES_HPP
