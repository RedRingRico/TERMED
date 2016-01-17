#ifndef __TERMED_OPENGLWINDOW_H__
#define __TERMED_OPENGLWINDOW_H__

#include <EditorWindow.h>
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GLText.h>
#include <Camera.h>

namespace TERMED
{
	enum RENDER_TYPE
	{
		ORTHOGRAPHIC_3D,
		PERSPECTIVE_3D,
		AXIS_XY,
		AXIS_XZ,
		AXIS_ZY
	};

	class OpenGLWindow : public EditorWindow
	{
	public:
		explicit OpenGLWindow( HGLRC p_GLContext );
		virtual ~OpenGLWindow( );

		virtual void SetDeviceContext( HDC p_DeviceContext );
		virtual void SetParentWindow( HWND p_ParentWindow );

		void SetClearColour( float p_Red, float p_Green, float p_Blue );

		void SetRenderType( RENDER_TYPE p_RenderType );

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

		RENDER_TYPE	m_RenderType;

		int	m_Width;
		int	m_Height;

		Camera	m_Camera;
		float			m_ViewScale;
	};
}

#endif // __TERMED_OPENGLWINDOW_H__
