#include <windows.h>

#define IDM_QUIT	1

// Prototypes
LRESULT CALLBACK EditorWindowProc( HWND p_WindowHandle, UINT p_Message,
	WPARAM p_WordParam, LPARAM p_LongParam );
void AddMenus( HWND p_WindowHandle );

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

		return 1;
	}

	ShowWindow( MainWindowHandle, SW_SHOWMAXIMIZED );
	SetForegroundWindow( MainWindowHandle );
	SetFocus( MainWindowHandle );

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
	}

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
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			break;
		}
		default:
		{
			return DefWindowProc( p_WindowHandle, p_Message, p_WordParam,
				p_LongParam );
		}
	}
}

void AddMenus( HWND p_WindowHandle )
{
	HMENU MenuBar;
	HMENU Menu;

	MenuBar = CreateMenu( );
	Menu = CreateMenu( );

	AppendMenu( Menu, MF_STRING, IDM_QUIT, "&Quit" );
	AppendMenu( MenuBar, MF_POPUP, ( UINT_PTR )Menu, "&File" );

	SetMenu( p_WindowHandle, MenuBar );
}
