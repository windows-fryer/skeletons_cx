#ifndef SKELETONS_CX_QANGLE_HPP
#define SKELETONS_CX_QANGLE_HPP

namespace sdk
{
	// Always use floats for view angles. This is for the sake of precision.

	struct qangle {
		float pitch{ }, yaw{ }, roll{ };

		qangle( ) = default;
		qangle( float pitch, float yaw, float roll ) : pitch( pitch ), yaw( yaw ), roll( roll ){ };
	};
} // namespace sdk

#endif // SKELETONS_CX_QANGLE_HPP
