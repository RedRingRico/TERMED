#ifndef __TERMED_OPENGLWINDOW_H__
#define __TERMED_OPENGLWINDOW_H__

#include <EditorWindow.h>
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GLText.h>

namespace TERMED
{
	class OpenGLWindow : public EditorWindow
	{
	public:
		explicit OpenGLWindow( HGLRC p_GLContext );
		virtual ~OpenGLWindow( );

		virtual void SetDeviceContext( HDC p_DeviceContext );
		virtual void SetParentWindow( HWND p_ParentWindow );

		void SetClearColour( float p_Red, float p_Green, float p_Blue );

		void SetActive( );

		void Clear( );
		void SwapBuffers( );

		static int RegisterWindow( );
		static void UnregisterWindow( );

	private:
		LRESULT CALLBACK WindowProc( UINT p_Message, WPARAM p_WordParam,
			LPARAM p_LongParam );

		static LRESULT CALLBACK InitialWindowProc( HWND p_WindowHandle,
			UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam );

		static LRESULT CALLBACK StaticWindowProc( HWND p_WindowHandle,
			UINT p_Message, WPARAM p_WordPara, LPARAM p_LongParam );

		HGLRC	m_GLContext;
		GLText	*m_pText;

		float	m_Red;
		float	m_Green;
		float	m_Blue;
	};
}

#endif // __TERMED_OPENGLWINDOW_H__