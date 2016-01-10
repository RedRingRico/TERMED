#include <GLText.h>
#include <cstdarg>
#include <cstring>

namespace TERMED
{
	GLText::GLText( HDC p_DeviceContext ) :
		m_FontBase( 0 ),
		m_Red( 1.0f ),
		m_Green( 1.0f ),
		m_Blue( 1.0f ),
		m_Alpha( 1.0f ),
		m_DeviceContext( p_DeviceContext ),
		m_ScreenWidth( 0.0f ),
		m_ScreenHeight( 0.0f ),
		m_Height( 0.0f )
	{
	}

	GLText::~GLText( )
	{
		glDeleteLists( m_FontBase, 96 );
	}

	int GLText::SetFont( const std::string &p_FontName )
	{
		m_FontBase = glGenLists( 96 );

		HFONT Font;

		Font = CreateFont( -7, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			p_FontName.c_str( ) );

		HFONT OldFont = ( HFONT )SelectObject( m_DeviceContext, Font );
		wglUseFontBitmaps( m_DeviceContext, 32, 96, m_FontBase );
		TEXTMETRIC Metrics;
		GetTextMetrics( m_DeviceContext, &Metrics );
		m_Height = Metrics.tmHeight;
		SelectObject( m_DeviceContext, OldFont );
		DeleteObject( OldFont );

		return 0;
	}

	void GLText::PrintString( const float p_X, const float p_Y,
		const std::string &p_String, ... )
	{
		char Text[ 512 ] = { '\0' };
		char StringCopy[ 512 ] = { '\0' };
		va_list ListPointer;

		if( p_String.size( ) == 0 )
		{
			return;
		}

		strncpy( StringCopy, p_String.c_str( ), p_String.size( ) );

		va_start( ListPointer, StringCopy );
		vsprintf( Text, p_String.c_str( ), ListPointer );
		va_end( ListPointer );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		glOrtho( 0, m_ScreenWidth, m_ScreenHeight, 0, 0, 1 );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		glTranslatef( 0.0f, 0.0f, -1.0f );

		glColor4f( m_Red, m_Green, m_Blue, m_Alpha );
		glRasterPos2f( p_X, p_Y );

		glPushAttrib( GL_LIST_BIT );
		glListBase( m_FontBase - 32 );
		glCallLists( p_String.size( ), GL_UNSIGNED_BYTE, Text );
		glPopAttrib( );
	}

	void GLText::SetScreenDimensions( const float p_Width, const float p_Height )
	{
		m_ScreenWidth = p_Width;
		m_ScreenHeight = p_Height;
	}

	float GLText::GetHeight( ) const
	{
		return m_Height;
	}
}
