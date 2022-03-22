#ifndef WEDNESDAY_WTF_UTILITIES_HPP
#define WEDNESDAY_WTF_UTILITIES_HPP

#include "../../globals/globals.hpp"
#include "../../sdk/structs/vector.hpp"

namespace utilities
{
	sdk::vector world_to_screen( sdk::vector position );
	sdk::vector world_to_screen( sdk::vector position, bool& on_screen );
} // namespace utilities

#endif // WEDNESDAY_WTF_UTILITIES_HPP
