//
// Created by Liga on 2/24/2022.
//

#ifndef SKELETONS_CX_COLOR_HPP
#define SKELETONS_CX_COLOR_HPP

namespace sdk
{
	struct color {
	public:
		float r{ }, g{ }, b{ }, a{ };

		color( ) = default;
		color( float r, float g, float b, float a ) : r( r ), g( g ), b( b ), a( a ) { }


	};
} // namespace sdk

#endif // SKELETONS_CX_COLOR_HPP
