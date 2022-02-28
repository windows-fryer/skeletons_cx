#include "math.hpp"

void math::angle_to_vector( const sdk::qangle& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up )
{
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos( &sp, &cp, DEG2RAD( angle.pitch ) );
	DirectX::XMScalarSinCos( &sy, &cy, DEG2RAD( angle.yaw ) );
	DirectX::XMScalarSinCos( &sr, &cr, DEG2RAD( angle.roll ) );

	if ( forward != nullptr ) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if ( right != nullptr ) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up != nullptr ) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

sdk::vector math::angle_to_vector( const sdk::qangle& angle )
{
	const auto sy = std::sin( angle.yaw / 180.f * PI );
	const auto cy = std::cos( angle.yaw / 180.f * PI );

	const auto sp = std::sin( angle.pitch / 180.f * PI );
	const auto cp = std::cos( angle.pitch / 180.f * PI );

	return sdk::vector( cp * cy, cp * sy, -sp );
}

sdk::qangle math::vector_to_angle( const sdk::vector& forward )
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

sdk::vector math::vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix )
{
	sdk::vector output{ };

	for ( int i = 0; i < 3; i++ )
		output[ i ] = vector1.dot( matrix.data[ i ] ) + matrix.data[ i ][ 3 ];

	return output;
}

// added another due to: what the fuck is this?????????
float math::get_fov( const sdk::qangle& view_angles, const sdk::vector& start, const sdk::vector& end )
{
	sdk::vector forward, direction = ( end - start ).normalized( );

	forward = angle_to_vector( view_angles );

	return std::max( RAD2DEG( std::acos( forward.dot_product( direction ) ) ), 0.f );
}

float math::calculate_angle_fov( const sdk::qangle& ang1, const sdk::qangle& ang2 )
{
	sdk::vector ang, aim;

	aim = angle_to_vector( ang1 );
	ang = angle_to_vector( ang2 );

	return RAD2DEG( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
}