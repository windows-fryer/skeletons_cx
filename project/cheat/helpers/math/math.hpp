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
	sdk::qangle vector_to_angle( const sdk::vector& forward )
	{
		float pitch, yaw, buffer;

		if ( forward.y == 0 && forward.x == 0 ) {
			yaw = 0;

			if ( forward.z > 0 )
				pitch = 270;
			else
				pitch = 90;
		} else {
			yaw = RAD2DEG( atan2f( forward.y, forward.x ) );

			if ( yaw < 0 )
				yaw += 360;

			buffer = forward.length_2d( );

			pitch = RAD2DEG( atan2f( -forward.z, buffer ) );

			if ( pitch < 0 )
				pitch += 360;
		}

		return { pitch, yaw, 0 };
	}

	sdk::vector angle_to_vector( const sdk::qangle& angle )
	{
		const auto sy = std::sin( angle.yaw / 180.f * PI );
		const auto cy = std::cos( angle.yaw / 180.f * PI );

		const auto sp = std::sin( angle.pitch / 180.f * PI );
		const auto cp = std::cos( angle.pitch / 180.f * PI );

		return sdk::vector( cp * cy, cp * sy, -sp );
	}

} // namespace math

#endif // SKELETONS_CX_MATH_HPP