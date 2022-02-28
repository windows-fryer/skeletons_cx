#ifndef SKELETONS_CX_MATH_HPP
#define SKELETONS_CX_MATH_HPP

#include <cmath>
#include <directxmath.h>

#include "../../sdk/structs/matrix.hpp"
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

	sdk::vector vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix );

	float get_fov( sdk::qangle view_angles, sdk::vector start, sdk::vector end );
} // namespace math

#endif // SKELETONS_CX_MATH_HPP
