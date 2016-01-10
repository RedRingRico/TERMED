#ifndef __TERMED_GLTEXT_H__
#define __TERMED_GLTEXT_H__

#include <windows.h>
#include <GL/gl.h>
#include <string>

namespace TERMED
{
	class GLText
	{
	public:
		explicit GLText( HDC p_DeviceContext );
		~GLText( );

		int SetFont( const std::string &p_FontName );
		void PrintString( const float p_X, const float p_Y,
			const std::string &p_String, ... );

		void SetScreenDimensions( const float p_Width, const float p_Height );

		float GetHeight( ) const;

	private:
		GLText( GLText &p_Copy );
		GLText &operator=( const GLText &p_Clone );

		GLuint	m_FontBase;
		GLfloat	m_Red;
		GLfloat	m_Green;
		GLfloat	m_Blue;
		GLfloat	m_Alpha;
		HDC		m_DeviceContext;
		float	m_ScreenWidth;
		float	m_ScreenHeight;
		float	m_Height;
	};
}

#endif // __TERMED_GLTEXT_H__
