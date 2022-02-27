#ifndef SKELETONS_CX_RENDERER_HPP
#define SKELETONS_CX_RENDERER_HPP

#include <deque>

#include "../../sdk/structs/color.hpp"
#include "../../sdk/structs/vector.hpp"

#pragma comment( lib, "d3d9" )
#pragma comment( lib, "d3dx9" )

enum font_flags : unsigned {
	FLAG_NONE,
	FLAG_DROPSHADOW,
	FLAG_OUTLINE,
	FLAG_OUTLINE_SEMI
};

enum class gradient_type_t
{
	HORIZONTAL = 0,
	VERTICAL
};

enum font_alignment : unsigned {
	AL_DEFAULT           = ( 1 << 0 ),
	AL_VERTICAL_TOP      = ( 1 << 1 ),
	AL_VERTICAL_CENTER   = ( 1 << 2 ),
	AL_HORIZONTAL_LEFT   = ( 1 << 3 ),
	AL_HORIZONTAL_CENTER = ( 1 << 4 ),
};

class vertex
{
public:
	float x{ }, y{ }, z{ }, rhw{ };
	D3DCOLOR _color{ };
	D3DXVECTOR2 position{ }, tex_coord{ };

	vertex( ) = default;

	vertex( const float x, const float y, sdk::color c )
	{
		this->x      = x;
		this->y      = y;
		this->_color = c.to_d3d( );
	}

	vertex( int x, int y, sdk::color c )
	{
		this->x      = static_cast< float >( x );
		this->y      = static_cast< float >( y );
		this->_color = c.to_d3d( );
	}

	vertex( float x, float y, float w, float h, sdk::color c )
	{
		this->position  = { x, y };
		this->tex_coord = { w, h };
		this->_color    = c.to_d3d( );
	}
	vertex( int x, int y, int w, int h, sdk::color c )
	{
		this->position  = { static_cast< float >( x ), static_cast< float >( y ) };
		this->tex_coord = { static_cast< float >( w ), static_cast< float >( h ) };
		this->_color    = c.to_d3d( );
	}

	vertex( const D3DXVECTOR2& pos, const D3DXVECTOR2& coord = D3DXVECTOR2( 0, 0 ) )
	{
		this->position  = pos;
		this->tex_coord = coord;
	}
};

struct font {
	LPD3DXFONT _font;
	std::uint32_t name;
};

namespace render
{
	inline IDirect3DDevice9* device;
	inline IDirect3DStateBlock9* state;
	inline IDirect3DVertexDeclaration9* vertex_declaration;
	inline IDirect3DVertexShader9* vertex_shader;
	inline DWORD color_write, srgb_write;

	struct impl {
		void init( IDirect3DDevice9* buffer_device );

		void setup_state( );
		void finish_state( );

		void create_font( std::size_t size, std::size_t weight, bool anti_aliased, const char* name, LPD3DXFONT& font );

		void render_line( int x, int y, int width, int height, sdk::color color );

		void render_rectangle( int x, int y, int width, int height, sdk::color color );
		template< class T = int >
		void render_rectangle( const sdk::vector& pos, const sdk::vector& size, sdk::color color );

		void render_filled_rectangle( int x, int y, int width, int height, sdk::color color );
		template< class T >
		void render_filled_rectangle( const sdk::vector& pos, const sdk::vector& size, sdk::color color );

		D3DXVECTOR2 render_text_size( const char* string, LPD3DXFONT font );

		void render_text( int x, int y, unsigned int alignment, const font_flags flags, const char* string, LPD3DXFONT font, sdk::color color );
		template< class T = int >
		void render_text( const sdk::vector& pos, unsigned int alignment, const font_flags flags, const char* string, LPD3DXFONT font,
		                  sdk::color color );

		void render_circle( int x, int y, int radius, int segments, sdk::color color );
		template< class T = int >
		void render_circle( const sdk::vector& pos, const sdk::vector& size, sdk::color color );

		template< auto gradient_type = gradient_type_t::HORIZONTAL >
		void render_gradient( int x, int y, int width, int height, sdk::color from, sdk::color to );

		template< auto gradient_type = gradient_type_t::HORIZONTAL, class T = int >
		void render_gradient( const sdk::vector& pos, const sdk::vector& size, sdk::color from, sdk::color to );

		// ty aiden
		template< class T = int >
		void quadratic_curve( const sdk::vector& start, const sdk::vector& control, const sdk::vector& end, sdk::color color );

		D3DVIEWPORT9 get_viewport( );
		bool set_viewport( const sdk::vector& pos, const sdk::vector& size );
		bool set_viewport( D3DVIEWPORT9 vp );
	};
} // namespace render
inline render::impl g_render;

namespace fonts
{
	struct impl {
		std::deque< font > font_list;

		void create_font( const char* name, std::size_t size, std::size_t weight, bool anti_aliased, const char* font_name );

		LPD3DXFONT find( std::uint32_t hashed )
		{
			for ( auto iterator = font_list.begin( ); iterator != font_list.end( ); iterator++ ) {
				if ( iterator->name == hashed )
					return iterator->_font;
			}

			return nullptr;
		}

		LPD3DXFONT operator[]( std::uint32_t hash )
		{
			return find( hash );
		}

		LPD3DXFONT operator[]( std::string string )
		{
			return find( fnv( string.c_str( ) ) );
		}
	};
} // namespace fonts

inline fonts::impl g_fonts;

#include "renderer.inl"

#endif // SKELETONS_CX_RENDERER_HPP
