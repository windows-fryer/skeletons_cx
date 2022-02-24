//
// Created by Liga on 2/23/2022.
//

#ifndef SKELETONS_CX_VECTOR_HPP
#define SKELETONS_CX_VECTOR_HPP

namespace sdk
{
	struct vector {
	public:
		float x{ }, y{ }, z{ };

		vector( ) = default;
		vector( float x, float y, float z ) : x( x ), y( y ), z( z ){ };
	};
} // namespace sdk

#endif // SKELETONS_CX_VECTOR_HPP
