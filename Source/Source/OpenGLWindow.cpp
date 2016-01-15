#include <OpenGLWindow.h>
#include <cassert>

namespace TERMED
{
	OpenGLWindow::OpenGLWindow( HGLRC p_GLContext ) :
		m_GLContext( p_GLContext ),
		m_pText( NULL ),
		m_Red( 0.0f ),
		m_Green( 0.0f ),
		m_Blue( 0.0f ),
		m_RenderType( PERSPECTIVE_3D ),
		m_Width( 0 ),
		m_Height( 0 )
	{
		m_ParentWindow = m_WindowHandle = NULL;
	}

	OpenGLWindow::~OpenGLWindow( )
	{
		delete m_pText;
	}

	void OpenGLWindow::SetDeviceContext( HDC p_DeviceContext )
	{
		EditorWindow::SetDeviceContext( p_DeviceContext );

		if( m_pText )
		{
			delete m_pText;
			m_pText = NULL;
		}

		this->SetActive( );
		m_pText = new GLText( m_DeviceContext );
		m_pText->SetFont( "System" );
	}

	void OpenGLWindow::SetParentWindow( HWND p_ParentWindow )
	{
		EditorWindow::SetParentWindow( p_ParentWindow );

		RECT WindowRect;

		GetClientRect( p_ParentWindow, &WindowRect );

		m_WindowHandle = CreateWindowEx( WS_EX_CLIENTEDGE, "TERMED OpenGL",
			NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			0, 0, WindowRect.right, WindowRect.bottom, m_ParentWindow, NULL,
			GetModuleHandle( NULL ), this );

		m_DeviceContext = GetDC( m_WindowHandle );

		PIXELFORMATDESCRIPTOR PixelFormatDescriptor =
		{
			sizeof( PIXELFORMATDESCRIPTOR ), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |//PFD_DOUBLEBUFFER |
					PFD_TYPE_RGBA,
				32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, 0,
				PFD_MAIN_PLANE, 0, 0, 0, 0
		};

		GLuint PixelFormat = ChoosePixelFormat( m_DeviceContext,
			&PixelFormatDescriptor );

		if( PixelFormat == 0 )
		{
			MessageBox( NULL, "Failed to chosse a pixel format", "TERMED",
				MB_OK | MB_ICONERROR );

			return;
		}

		if( SetPixelFormat( m_DeviceContext, PixelFormat,
			&PixelFormatDescriptor ) == 0 )
		{
			MessageBox( NULL, "Failed to set pixel format", "TERMED",
				MB_OK | MB_ICONERROR );

			return;
		}

		m_pText->SetScreenDimensions( WindowRect.right, WindowRect.bottom );
	}

	void OpenGLWindow::SetClearColour( float p_Red, float p_Green,
		float p_Blue )
	{
		m_Red = p_Red;
		m_Green = p_Green;
		m_Blue = p_Blue;
	}

	void OpenGLWindow::SetRenderType( RENDER_TYPE p_RenderType )
	{
		m_RenderType = p_RenderType;
	}

	void OpenGLWindow::SetActive( )
	{
		wglMakeCurrent( m_DeviceContext, m_GLContext );
	}

	void OpenGLWindow::Clear( )
	{
		glViewport( 0, 0, m_Width, m_Height );
		glScissor( 0, 0, m_Width, m_Height );
		glClearColor( m_Red, m_Green, m_Blue, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	void OpenGLWindow::SwapBuffers( )
	{
		RECT WindowRect;

		GetClientRect( m_WindowHandle, &WindowRect );

		glDisable( GL_DEPTH_TEST );
		std::string RenderString;

		switch( m_RenderType )
		{
			case ORTHOGRAPHIC_3D:
			{
				RenderString = "Orthographic";
				break;
			}
			case PERSPECTIVE_3D:
			{
				RenderString = "Perspective";
				break;
			}
			case AXIS_XY:
			{
				RenderString = "[XY]";
				break;
			}
			case AXIS_XZ:
			{
				RenderString = "[XZ]";
				break;
			}
			case AXIS_ZY:
			{
				RenderString = "[ZY]";
				break;
			}
		}
		m_pText->PrintString( 10.0f, WindowRect.bottom - m_pText->GetHeight( ),
			RenderString );
		glEnable( GL_DEPTH_TEST );

		::SwapBuffers( m_DeviceContext );
	}

	int OpenGLWindow::RegisterWindow( )
	{
		WNDCLASS WindowClass;

		if( GetClassInfo( GetModuleHandle( NULL ), "TERMED OpenGL",
			&WindowClass ) == FALSE )
		{
			WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			WindowClass.cbClsExtra = 0;
			WindowClass.cbWndExtra = sizeof( OpenGLWindow * );
			WindowClass.lpfnWndProc = &OpenGLWindow::InitialWindowProc;
			WindowClass.lpszClassName = "TERMED OpenGL";
			WindowClass.lpszMenuName = NULL;
			WindowClass.hInstance = GetModuleHandle( NULL );
			WindowClass.hbrBackground = NULL;
			WindowClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
			WindowClass.hCursor = LoadCursor( NULL, IDC_ARROW );

			if( !RegisterClass( &WindowClass ) )
			{
				MessageBox( NULL, "Failed to register the OpenGL window class",
					"TERMED", MB_OK | MB_ICONERROR );
				return 1;
			}
		}

		return 0;
	}

	void OpenGLWindow::UnregisterWindow( )
	{
		UnregisterClass( "TERMED OpenGL", GetModuleHandle( NULL ) );
	}

	LRESULT CALLBACK OpenGLWindow::WindowProc( UINT p_Message,
		WPARAM p_WordParam, LPARAM p_LongParam )
	{
		switch( p_Message )
		{
			case WM_CREATE:
			{
				break;
			}
			case WM_SIZE:
			{
				m_Width = LOWORD( p_LongParam );
				m_Height = HIWORD( p_LongParam );
				m_pText->SetScreenDimensions( LOWORD( p_LongParam ), HIWORD( p_LongParam ) );

				RECT WindowRect;
				GetWindowRect( m_WindowHandle, &WindowRect );
				ValidateRect( m_WindowHandle, &WindowRect );

				break;
			}
			case WM_ERASEBKGND:
			{
				return 1;
			}
			default:
			{
				return DefWindowProc( m_WindowHandle, p_Message, p_WordParam,
					p_LongParam );
			}
		}
		return 0L;
	}

	LRESULT CALLBACK OpenGLWindow::InitialWindowProc( HWND p_WindowHandle,
		UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam )
	{
		if( p_Message == WM_NCCREATE )
		{
			LPCREATESTRUCT CreateStruct =
				reinterpret_cast< LPCREATESTRUCT >( p_LongParam );
			void *pCreateParam = CreateStruct->lpCreateParams;
			OpenGLWindow *pThis =
				reinterpret_cast< OpenGLWindow * >( pCreateParam );
			pThis->m_WindowHandle = p_WindowHandle;

			SetWindowLongPtr( pThis->m_WindowHandle, GWLP_USERDATA,
				reinterpret_cast< LONG_PTR >( pThis ) );
			SetWindowLongPtr( pThis->m_WindowHandle, GWLP_WNDPROC,
				reinterpret_cast< LONG_PTR >(
					&OpenGLWindow::StaticWindowProc ) );

			return pThis->WindowProc( p_Message, p_WordParam, p_LongParam );
		}

		return DefWindowProc( p_WindowHandle, p_Message, p_WordParam,
			p_LongParam );
	}

	LRESULT CALLBACK OpenGLWindow::StaticWindowProc( HWND p_WindowHandle,
		UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam )
	{
		LONG_PTR UserData = GetWindowLongPtr( p_WindowHandle, GWLP_USERDATA );
		OpenGLWindow *pThis = reinterpret_cast< OpenGLWindow * >( UserData );
		
		assert( pThis );
		assert( p_WindowHandle == pThis->m_WindowHandle );

		return pThis->WindowProc( p_Message, p_WordParam, p_LongParam );
	}
}
