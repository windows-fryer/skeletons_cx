#ifndef SKELETONS_CX_MATH_HPP
#define SKELETONS_CX_MATH_HPP

#include <DirectXMath.h>
#include <cmath>

#include "../sdk/structs/vector.hpp"
#include "../sdk/structs/qangle.hpp"

#define PI 3.14159265358979323846f
#define RADPI 57.295779513082f
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)


namespace math{

	sdk::qangle vector_to_angle(const sdk::vector& forward) {
		float pitch, yaw, buffer;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = RAD2DEG(atan2f(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			buffer = forward.length_2d();

			pitch = RAD2DEG(atan2f(-forward.z, buffer));

			if (pitch < 0)
				pitch += 360;
		}

		return {pitch, yaw, 0};
	}


}



#endif // SKELETONS_CX_MATH_HPP
