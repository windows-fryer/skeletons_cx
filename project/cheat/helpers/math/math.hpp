#ifndef SKELETONS_CX_MATH_HPP
#define SKELETONS_CX_MATH_HPP

#include <cmath>
#include <directxmath.h>

#include "../../sdk/structs/qangle.hpp"
#include "../../sdk/structs/vector.hpp"

#define PI           3.14159265358979323846f
#define RADPI        57.295779513082f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )

namespace math
{
	sdk::qangle vector_to_angle( const sdk::vector& forward );

	sdk::vector angle_to_vector( const sdk::qangle& angle );

	void angle_to_vector( const sdk::qangle& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up );
} // namespace math

#endif // SKELETONS_CX_MATH_HPP
