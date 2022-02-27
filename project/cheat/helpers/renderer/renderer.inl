#ifndef SKELETONS_CX_RENDERER_INL
#define SKELETONS_CX_RENDERER_INL

#include "renderer.hpp"

template< class T >
void render::impl::render_circle( const sdk::vector& pos, const sdk::vector& size, sdk::color color )
{
	render_circle( pos.x, pos.y, size.x, size.y, color );
}

template< auto gradient_type >
void render::impl::render_gradient( int x, int y, int width, int height, sdk::color from, sdk::color to )
{
	if ( !render::device )
		return;

	struct vertex_mod {
		float x, y, z, rhw;
		D3DCOLOR c;
	};

	vertex_mod verts[ 4 ] = { { static_cast< float >( x ), static_cast< float >( y ), 0.01f, 0.01f, from.to_d3d( ) },
		                      { static_cast< float >( x + width ), static_cast< float >( y ), 0.01f, 0.01f,
		                        gradient_type == gradient_type_t::HORIZONTAL ? to.to_d3d( ) : from.to_d3d( ) },
		                      { static_cast< float >( x ), static_cast< float >( y + height ), 0.01f, 0.01f,
		                        gradient_type == gradient_type_t::HORIZONTAL ? from.to_d3d( ) : to.to_d3d( ) },
		                      { static_cast< float >( x + width ), static_cast< float >( y + height ), 0.01f, 0.01f, to.to_d3d( ) } };

	device->SetTexture( 0, nullptr );
	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &verts, 20 );
}

template< auto gradient_type, class T >
void render::impl::render_gradient( const sdk::vector& pos, const sdk::vector& size, sdk::color from, sdk::color to )
{
	render_gradient< gradient_type >( pos.x, pos.y, size.x, size.y, from, to );
}

template< class T >
void render::impl::render_rectangle( const sdk::vector& pos, const sdk::vector& size, sdk::color color )
{
	render_rectangle( pos.x, pos.y, size.x, size.y, color );
}

template< class T >
void render::impl::render_filled_rectangle( const sdk::vector& pos, const sdk::vector& size, sdk::color color )
{
	render_filled_rectangle( pos.x, pos.y, size.x, size.y, color );
}

template< class T >
void render::impl::render_text( const sdk::vector& pos, unsigned int alignment, const font_flags flags, const char* string, LPD3DXFONT font,
                                sdk::color color )
{
	render_text( pos.x, pos.y, alignment, flags, string, font, color );
}

template< class T >
void render::impl::quadratic_curve( const sdk::vector& start, const sdk::vector& control, const sdk::vector& end, sdk::color color )
{
	if ( !render::device )
		return;

	float iterator      = 0.01;
	const auto segments = 1 / iterator;
	static auto verts   = static_cast< vertex* >( _malloca( sizeof( vertex ) * ( segments + 2 ) ) );

	constexpr auto lerp = [ & ]( float interp, const sdk::vector& min, const sdk::vector& max ) -> sdk::vector {
		sdk::vector lerped;
		lerped.x = ( max.x - min.x ) * interp + min.x;
		lerped.y = ( max.y - min.y ) * interp + min.y;
		return lerped;
	};

	constexpr auto quadtratic = [ & ]( float interp, const sdk::vector& start, const sdk::vector& end, const sdk::vector& control ) -> sdk::vector {
		sdk::vector start_buffer{ }, end_buffer{ };

		start_buffer = lerp( interp, start, end );
		end_buffer   = lerp( interp, end, control );

		return lerp( interp, start_buffer, end_buffer );
	};

	if ( !verts )
		return;

	for ( int i = 0; i < segments + 2; i++ ) {
		sdk::vector curve = quadtratic( i * iterator, start, end, control );
		verts[ i ].x      = curve.x;
		verts[ i ].y      = curve.y;
		verts[ i ].z      = 0;
		verts[ i ].rhw    = 1;
		verts[ i ]._color = color.to_d3d( );
	}

	device->SetTexture( 0, nullptr );
	device->DrawPrimitiveUP( D3DPT_LINESTRIP, segments, verts, 20 );
}

#endif // SKELETONS_CX_RENDERER_INL
