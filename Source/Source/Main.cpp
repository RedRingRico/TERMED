#include <windows.h>
#include <OpenGLWindow.h>
#include <WindowSplitter.h>

#define IDM_QUIT	1

// Prototypes
LRESULT CALLBACK EditorWindowProc( HWND p_WindowHandle, UINT p_Message,
	WPARAM p_WordParam, LPARAM p_LongParam );
void AddMenus( HWND p_WindowHandle );


// Globals
TERMED::OpenGLWindow *g_pTestGL[ 4 ];

TERMED::WindowSplitter *g_pSplitter;

INT WINAPI WinMain( HINSTANCE p_ThisInstance, HINSTANCE p_PrevInstance,
	LPSTR p_CmdLine, INT p_Cmd )
{
	WNDCLASS WindowClass;

	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.lpfnWndProc = EditorWindowProc;
	WindowClass.lpszClassName = "TERMED MAIN";
	WindowClass.lpszMenuName = NULL;
	WindowClass.hInstance = p_ThisInstance;
	WindowClass.hbrBackground = NULL;
	WindowClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	WindowClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	
	if( !RegisterClass( &WindowClass ) )
	{
		MessageBox( NULL, "Failed to register editor window class", "TERMED",
			MB_OK | MB_ICONERROR );

		return 1;
	}

	HWND MainWindowHandle;

	MainWindowHandle = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		"TERMED MAIN", "TERMED", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		p_ThisInstance, NULL );

	if( MainWindowHandle == NULL )
	{
		MessageBox( NULL, "Failed to create main window", "TERMED",
			MB_OK | MB_ICONERROR );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	PIXELFORMATDESCRIPTOR PixelFormatDescriptor =
	{
		sizeof( PIXELFORMATDESCRIPTOR ), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER |
			PFD_TYPE_RGBA,
		32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	HDC DeviceContext;

	DeviceContext = GetDC( MainWindowHandle );
	if( DeviceContext == NULL )
	{
		MessageBox( NULL, "Failed to get device context for the window",
			"TERMED", MB_OK | MB_ICONERROR );
		
		DestroyWindow( MainWindowHandle );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	GLuint PixelFormat;

	PixelFormat = ChoosePixelFormat( DeviceContext, &PixelFormatDescriptor );

	if( PixelFormat == 0 )
	{
		MessageBox( NULL, "Failed to choose a pixel format", "TERMED",
			MB_OK | MB_ICONERROR );
	
		ReleaseDC( MainWindowHandle, DeviceContext );
		DestroyWindow( MainWindowHandle );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	if( SetPixelFormat( DeviceContext, PixelFormat,
		&PixelFormatDescriptor ) == 0 )
	{
		MessageBox( NULL, "Failed to set pixel format", "TERMED",
			MB_OK | MB_ICONERROR );

		ReleaseDC( MainWindowHandle, DeviceContext );
		DestroyWindow( MainWindowHandle );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	HGLRC GLContext;
	GLContext = wglCreateContext( DeviceContext );

	if( GLContext == NULL )
	{
		MessageBox( NULL, "Failed to create an OpenGL context", "TERMED",
			MB_OK | MB_ICONERROR );

		ReleaseDC( MainWindowHandle, DeviceContext );
		DestroyWindow( MainWindowHandle );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	if( wglMakeCurrent( DeviceContext, GLContext ) == 0 )
	{
		MessageBox( NULL, "Failed to make the OpenGL context current",
			"TERMED", MB_OK | MB_ICONERROR );

		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( GLContext );

		ReleaseDC( MainWindowHandle, DeviceContext );
		DestroyWindow( MainWindowHandle );
		UnregisterClass( "TERMED MAIN", p_ThisInstance );

		return 1;
	}

	ShowWindow( MainWindowHandle, SW_SHOWMAXIMIZED );
	SetForegroundWindow( MainWindowHandle );
	SetFocus( MainWindowHandle );

	glViewport( 0, 0, 800, 600 );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	wglMakeCurrent( NULL, NULL );

	TERMED::OpenGLWindow::RegisterWindow( );
	TERMED::WindowSplitter::RegisterWindow( );

	g_pSplitter = new TERMED::WindowSplitter( TERMED::SPLIT_TYPE_FOUR_WAY );
	g_pSplitter->SetDeviceContext( DeviceContext );
	g_pSplitter->SetParentWindow( MainWindowHandle );

	for( int i = 0; i < 4; ++i )
	{
		g_pTestGL[ i ] = new TERMED::OpenGLWindow( GLContext );	
		g_pTestGL[ i ]->SetDeviceContext( g_pSplitter->GetDeviceContext( ) );
		g_pTestGL[ i ]->SetParentWindow( g_pSplitter->GetWindowHandle( ) );
	}

	g_pTestGL[ 0 ]->SetClearColour( 0.0f, 17.0f / 255.0f, 43.0f / 255.0f );
	g_pTestGL[ 1 ]->SetClearColour( 1.0f, 17.0f / 255.0f, 43.0f / 255.0f );
	g_pTestGL[ 2 ]->SetClearColour( 0.0f, 1.0f, 43.0f / 255.0f );
	g_pTestGL[ 3 ]->SetClearColour( 0.0f, 17.0f / 255.0f, 1.0f );

	for( int i = 0; i < 4; ++i )
	{
		g_pSplitter->SetWindow( i, g_pTestGL[ i ] );
	}

	g_pSplitter->CentreSplitter( );

	MSG Message;

	bool Run = true;

	while( Run )
	{
		if( PeekMessage( &Message, NULL, 0, 0, PM_REMOVE ) )
		{
			if( Message.message == WM_QUIT )
			{
				Run = false;
				continue;
			}

			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}

		for( int i = 0; i < 4; ++i )
		{
			g_pTestGL[ i ]->SetActive( );
			g_pTestGL[ i ]->Clear( );
			g_pTestGL[ i ]->SwapBuffers( );
		}
	}

	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( GLContext );

	ReleaseDC( MainWindowHandle, DeviceContext );
	DestroyWindow( MainWindowHandle );
	UnregisterClass( "TERMED MAIN", p_ThisInstance );

	for( int i = 0; i < 4; ++i )
	{
		delete g_pTestGL[ i ];
	}

	delete g_pSplitter;

	TERMED::OpenGLWindow::UnregisterWindow( );
	TERMED::WindowSplitter::UnregisterWindow( );

	return 0;
}


LRESULT CALLBACK EditorWindowProc( HWND p_WindowHandle, UINT p_Message,
	WPARAM p_WordParam, LPARAM p_LongParam )
{
	switch( p_Message )
	{
		case WM_CREATE:
		{
			AddMenus( p_WindowHandle );

			break;
		}
		case WM_COMMAND:
		{
			switch( p_WordParam )
			{
				case IDM_QUIT:
				{
					SendMessage( p_WindowHandle, WM_CLOSE, 0, 0 );
					break;
				}
				default:
				{
					break;
				}
			}

			break;
		}
		case WM_SIZE:
		{
			RECT WindowRect;
			WindowRect.left = 0;
			WindowRect.right = LOWORD( p_LongParam );
			WindowRect.top = 0;
			WindowRect.bottom = HIWORD( p_LongParam );

			if( g_pSplitter )
			{
				MoveWindow( g_pSplitter->GetWindowHandle( ), 0, 0,
					WindowRect.right - WindowRect.left,
					WindowRect.bottom - WindowRect.top, TRUE );
			}

			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			break;
		}
		default:
		{
			return DefWindowProc( p_WindowHandle, p_Message, p_WordParam,p_LongParam );
		}
	}

	return 0L;	
}

void AddMenus( HWND p_WindowHandle )
{
	HMENU MenuBar;
	HMENU FileMenu;
	HMENU ToolMenu;

	MenuBar = CreateMenu( );
	FileMenu = CreateMenu( );
	ToolMenu = CreateMenu( );

	AppendMenu( FileMenu, MF_STRING, 22, "&Save" );
	AppendMenu( FileMenu, MF_SEPARATOR, NULL, NULL );
	AppendMenu( FileMenu, MF_STRING, IDM_QUIT, "&Quit" );

	AppendMenu( ToolMenu, MF_STRING, 22, "&Cook" );
	AppendMenu( ToolMenu, MF_STRING, 22, "Connect to &Katana" );

	AppendMenu( MenuBar, MF_POPUP, ( UINT_PTR )FileMenu, "&File" );
	AppendMenu( MenuBar, MF_POPUP, ( UINT_PTR )ToolMenu, "&Tools" );

	SetMenu( p_WindowHandle, MenuBar );
}
