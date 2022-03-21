#include "renderer.hpp"
#include "../../globals/snakeify.hpp"

//-----------------------------------------------------------------------------
// @PURPOSE : Defines the device we will render with & our fonts.
// @INPUT   :
// 				buffer_device - The device we will render with.
//-----------------------------------------------------------------------------
void render::impl::init( IDirect3DDevice9* buffer_device )
{
	render::device = buffer_device;

	g_fonts.create_font( "main_font", 14, FW_NORMAL, true, "Tahoma" );
	g_fonts.create_font( "main_font_bold", 14, FW_BOLD, true, "Tahoma" );
	g_fonts.create_font( "main_verdana_font", 13, FW_NORMAL, true, "Verdana" );
	g_fonts.create_font( "main_verdana_bold_font", 13, FW_BOLD, true, "Verdana" );
	g_fonts.create_font( "indicator_verdana_font", 30, FW_BOLD, true, "Verdana" );

	g_fonts.create_font( "esp_font", 14, FW_BOLD, false, "Arial" );
	g_fonts.create_font( "esp_indicator_font", 13, FW_BOLD, false, "Smallest Pixel-7" );

	g_fonts.create_font( "menu_font", 12, FW_NORMAL, true, "Verdana" );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Creates a renderable state.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void render::impl::setup_state( )
{
	device->CreateStateBlock( D3DSBT_PIXELSTATE, &state );
	state->Capture( );
	device->GetVertexDeclaration( &vertex_declaration );
	device->GetVertexShader( &vertex_shader );

	device->SetVertexShader( nullptr );
	device->SetPixelShader( nullptr );
	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->SetRenderState( D3DRS_LIGHTING, false );
	device->SetRenderState( D3DRS_FOGENABLE, false );
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	device->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
	device->SetRenderState( D3DRS_ZWRITEENABLE, false );
	device->SetRenderState( D3DRS_STENCILENABLE, false );

	device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, false );
	device->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, true );

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_ALPHATESTENABLE, false );
	device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, true );
	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetRenderState( D3DRS_COLORWRITEENABLE,
	                        D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );

	device->GetTexture( 0, &texture );
	device->SetTexture( 0, nullptr );

	device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Restores our old non-renderable state.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void render::impl::finish_state( )
{
	state->Apply( );
	state->Release( );

	device->SetVertexDeclaration( vertex_declaration );
	device->SetVertexShader( vertex_shader );
	device->SetTexture( 0, texture );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Creates a font.
// @INPUT   :
//				size - The font size.
//				weight - The font weight.
//				anti_aliased - Smooth or jagged font.
//				name - TTF name for the font.
//				font - Reference to where the font should go.
//-----------------------------------------------------------------------------
void render::impl::create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font )
{
	DEVICE_SAFETY( );

	FAIL_CHECK( D3DXCreateFont( device, size, 0, weight, 1, false, DEFAULT_CHARSET, 1, anti_aliased ? ANTIALIASED_QUALITY : NONANTIALIASED_QUALITY,
	                            DEFAULT_PITCH, name, &font ) )
}

//-----------------------------------------------------------------------------
// @PURPOSE : Renders a line.
// @INPUT   :
//				x - Start of the line's X.
//				y - Start of the line's Y.
//				width - End of the line's X.
//				height - End of the line's Y.
//				color - Color for the line.
//-----------------------------------------------------------------------------
void render::impl::render_line( int x, int y, int width, int height, sdk::color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { width, height, color } };

	render::device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( render::device->DrawPrimitiveUP( D3DPT_LINELIST, 1, segments, sizeof( vertex ) ) );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Renders a non-filled rectangle.
// @INPUT   :
//				x - Start of the rectangle's X.
//				y - Start of the rectangle's Y.
//				width - End of the rectangle's X relative to x.
//				height - End of the rectangle's Y relative to y.
//-----------------------------------------------------------------------------
void render::impl::render_rectangle( int x, int y, int width, int height, sdk::color color )
{
	DEVICE_SAFETY( );

	g_render.render_line( x, y, x + width, y, color );
	g_render.render_line( x, y, x, y + height, color );
	g_render.render_line( x, y + height, x + width, y + height, color );
	g_render.render_line( x + width, y, x + width, y + height, color );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Renders a filled rectangle.
// @INPUT   :
//				x - Start of the rectangle's X.
//				y - Start of the rectangle's Y.
//				width - End of the rectangle's X relative to x.
//				height - End of the rectangle's Y relative to y.
//-----------------------------------------------------------------------------
void render::impl::render_filled_rectangle( int x, int y, int width, int height, sdk::color color )
{
	DEVICE_SAFETY( );

	vertex segments[]{ { x, y, color }, { x + width, y, color }, { x, y + height, color }, { x + width, y + height, color } };

	render::device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	FAIL_CHECK( render::device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, segments, sizeof( vertex ) ) );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Gets size of provided string.
// @INPUT   :
//				string - String you are trying to find the size of.
//				font - What font the string uses.
//-----------------------------------------------------------------------------
D3DXVECTOR2 render::impl::render_text_size( const char* string, LPD3DXFONT font )
{
	RECT rect{ 0, 0, 0, 0 };

	font->DrawTextA( nullptr, string, -1, &rect, DT_CALCRECT, sdk::color( 0, 0, 0, 0 ).to_d3d( ) );

	return D3DXVECTOR2( static_cast< const short >( rect.right - rect.left ), static_cast< const short >( rect.bottom - rect.top ) );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Gets our current device's viewport.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
D3DVIEWPORT9 render::impl::get_viewport( )
{
	D3DVIEWPORT9 vp{ };
	device->GetViewport( &vp );
	return vp;
}

//-----------------------------------------------------------------------------
// @PURPOSE : Sets our current device's viewport.
// @INPUT   :
//				pos - Start of our 2 axis vector containing X & Y.
//				size - End of our 2 axis vector containing X & Y.
//-----------------------------------------------------------------------------
bool render::impl::set_viewport( const sdk::vector& pos, const sdk::vector& size )
{
	const D3DVIEWPORT9 view = {
		static_cast< DWORD >( pos.x ), static_cast< DWORD >( pos.y ), static_cast< DWORD >( size.x ), static_cast< DWORD >( size.y ), 0, 1
	};

	return g_render.set_viewport( view );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Sets our current device's viewport.
// @INPUT   :
//				vp - DirectX viewport struct.
//-----------------------------------------------------------------------------
bool render::impl::set_viewport( D3DVIEWPORT9 vp )
{
	return device->SetViewport( &vp );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Renders a piece of text with a given font & string.
// @INPUT   :
//				x - Start of the text's X.
//				y - Start of the text's Y.
//				alignment - The font's alignment flag.
//				flags - The font's flags.
//				string - String wanting to be rendered.
//				font - Wanted font for rendering.
//				_color - Color for string.
//-----------------------------------------------------------------------------
void render::impl::render_text( int x, int y, unsigned int alignment, const font_flags flags, const char* string, LPD3DXFONT font, sdk::color _color )
{
	DEVICE_SAFETY( );

	RECT rect{ };

	D3DXVECTOR2 text_size = g_render.render_text_size( string, font );

	auto set_rect = []( RECT* rect, int x, int y ) { SetRect( rect, x, y, x, y ); };

	if ( alignment != font_alignment::AL_DEFAULT ) {
		if ( alignment & font_alignment::AL_VERTICAL_TOP )
			y -= text_size.y;
		else if ( alignment & font_alignment::AL_VERTICAL_CENTER )
			y -= text_size.y / 2;
		if ( alignment & font_alignment::AL_HORIZONTAL_LEFT )
			x -= text_size.x;
		else if ( alignment & font_alignment::AL_HORIZONTAL_CENTER )
			x -= text_size.x / 2;
	}

	if ( flags == font_flags::FLAG_NONE ) {
		set_rect( &rect, x, y );
		font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_d3d( ) );
	} else {
		if ( flags == font_flags::FLAG_DROPSHADOW ) {
			set_rect( &rect, x + 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );

			set_rect( &rect, x, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_d3d( ) );
		}

		if ( flags == font_flags::FLAG_OUTLINE ) {
			set_rect( &rect, x, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x + 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x - 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );

			set_rect( &rect, x + 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x - 1, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );

			set_rect( &rect, x + 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x - 1, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x + 1, y - 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x - 1, y + 1 );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );

			set_rect( &rect, x, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_d3d( ) );
		}
		if ( flags == font_flags::FLAG_OUTLINE_SEMI ) {
			set_rect( &rect, x - 1, y );
			font->DrawTextA( NULL, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x + 1, y );
			font->DrawTextA( NULL, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x, y - 1 );
			font->DrawTextA( NULL, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );
			set_rect( &rect, x, y + 1 );
			font->DrawTextA( NULL, string, -1, &rect, DT_LEFT | DT_NOCLIP, sdk::color( 0, 0, 0, _color.a ).to_d3d( ) );

			set_rect( &rect, x, y );
			font->DrawTextA( nullptr, string, -1, &rect, DT_LEFT | DT_NOCLIP, _color.to_d3d( ) );
		}
	}
}

//-----------------------------------------------------------------------------
// @PURPOSE : Renders a circle.
// @INPUT   :
// 				x - Start of the circle's X.
//				y - Start of the circle's Y.
//				radius - How big the circle is from its center.
// 				segments - How many points will be rendered in the circle.
//				color - Color of the circle.
//-----------------------------------------------------------------------------
void render::impl::render_circle( int x, int y, int radius, int segments, sdk::color color )
{
	vertex* verticies = new vertex[ segments + 1 ];

	for ( int iterator = 0; iterator <= segments; iterator++ )
		verticies[ iterator ] = vertex( x + radius * cos( D3DX_PI * ( iterator / ( segments / 2.f ) ) ),
		                                y + radius * sin( D3DX_PI * ( iterator / ( segments / 2.f ) ) ), color );

	device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	device->DrawPrimitiveUP( D3DPT_LINESTRIP, segments, verticies, sizeof( vertex ) );

	delete[] verticies;
}

//-----------------------------------------------------------------------------
// @PURPOSE : Creates a font for use.
// @INPUT   :
//				name - A unique for the font.
// 				size - Size of the font.
//				weight - Weight of the font.
//				anti_aliased - Smooth or jagged font.
//				font_name - TTF name for the font.
//-----------------------------------------------------------------------------
void fonts::impl::create_font( const char* name, std::size_t size, std::size_t weight, bool anti_aliased, const char* font_name )
{
	LPD3DXFONT buffer_font;

	g_render.create_font( size, weight, anti_aliased, font_name, buffer_font );

	font_list.push_back( { buffer_font, fnv( name ) } );
}
