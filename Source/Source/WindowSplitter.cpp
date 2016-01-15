#include <WindowSplitter.h>
#include <cassert>

namespace TERMED
{
	WindowSplitter::WindowSplitter( SPLIT_TYPE p_SplitType ) :
		m_SplitType( p_SplitType ),
		m_SplitterMoving( false ),
		m_SplitterMoveHorizontal( false ),
		m_SplitterMoveVertical( false )
	{
		m_pChildWindow[ 0 ] = m_pChildWindow[ 1 ] = 
			m_pChildWindow[ 2 ] = m_pChildWindow[ 3 ] = NULL;
		m_SplitterPosition.x = m_SplitterPosition.y = 0L;
	}

	WindowSplitter::~WindowSplitter( )
	{
	}

	void WindowSplitter::SetDeviceContext( HDC p_DeviceContext )
	{
		EditorWindow::SetDeviceContext( p_DeviceContext );
	}

	void WindowSplitter::SetParentWindow( HWND p_ParentWindow )
	{
		EditorWindow::SetParentWindow( p_ParentWindow );

		RECT WindowRect;

		GetClientRect( p_ParentWindow, &WindowRect );

		m_WindowHandle = CreateWindowEx( WS_EX_CLIENTEDGE, "TERMED | SPLITTER",
			NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0,
			WindowRect.right, WindowRect.bottom, m_ParentWindow, NULL,
			GetModuleHandle( NULL ), this );

		UpdateWindow( m_WindowHandle );
	}

	int WindowSplitter::SetWindow( size_t p_Index, EditorWindow *p_pWindow )
	{
		m_pChildWindow[ p_Index ] = p_pWindow;

		return 0;
	}

	void WindowSplitter::CentreSplitter( )
	{
		RECT Rect;
		GetClientRect( m_WindowHandle, &Rect );

		m_SplitterPosition.x = Rect.right / 2 - 1;
		m_SplitterPosition.y = Rect.bottom / 2 - 1;

		LONG SizeParam = MAKELONG( Rect.right, Rect.bottom );

		SendMessage( m_WindowHandle, WM_SIZE, 0, SizeParam );
	}

	int WindowSplitter::RegisterWindow( )
	{
		WNDCLASS WindowClass;

		if( GetClassInfo( GetModuleHandle( NULL ), "TERMED | SPLITTER",
			&WindowClass ) == FALSE )
		{
			WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			WindowClass.cbClsExtra = 0;
			WindowClass.cbWndExtra = sizeof( WindowSplitter * );
			WindowClass.lpfnWndProc = &WindowSplitter::InitialWindowProc;
			WindowClass.lpszClassName = "TERMED | SPLITTER";
			WindowClass.lpszMenuName = NULL;
			WindowClass.hInstance = GetModuleHandle( NULL );
			WindowClass.hbrBackground =  (HBRUSH)GetStockObject(LTGRAY_BRUSH);;
			WindowClass.hIcon = LoadIcon( NULL, IDI_WINLOGO );
			WindowClass.hCursor = LoadCursor( NULL, IDC_ARROW );

			if( !RegisterClass( &WindowClass ) )
			{
				MessageBox( NULL, "Failed to register the Splitter window "
					"class", "TERMED", MB_OK | MB_ICONERROR );

				return 1;
			}
		}

		return 0;
	}

	void WindowSplitter::UnregisterWindow( )
	{
		UnregisterClass( "TERMED | SPLITTER", GetModuleHandle( NULL ) );
	}

	LRESULT CALLBACK WindowSplitter::WindowProc( UINT p_Message,
		WPARAM p_WordParam, LPARAM p_LongParam )
	{
		switch( p_Message )
		{
			case WM_CREATE:
			{
				if( m_SplitType == SPLIT_TYPE_HORIZONTAL )
				{
					m_SplitterPosition.y =
						( ( LPCREATESTRUCT )p_LongParam )->cy / 2 - 1;
					m_Cursor = LoadCursor( NULL, MAKEINTRESOURCE( IDC_SIZENS ) );
				}
				else if( m_SplitType == SPLIT_TYPE_VERTICAL )
				{
					m_SplitterPosition.x =
						( ( LPCREATESTRUCT )p_LongParam )->cx / 2 - 1;
					m_Cursor = LoadCursor( NULL, MAKEINTRESOURCE( IDC_SIZEWE ) );
				}
				else
				{
					m_SplitterPosition.y =
						( ( LPCREATESTRUCT )p_LongParam )->cy / 2 - 1;
					m_SplitterPosition.x =
						( ( LPCREATESTRUCT )p_LongParam )->cx / 2 - 1;

					m_CursorNS = LoadCursor( NULL, MAKEINTRESOURCE( IDC_SIZENS ) );
					m_CursorWE = LoadCursor( NULL, MAKEINTRESOURCE( IDC_SIZEWE ) );
					m_Cursor = LoadCursor( NULL, MAKEINTRESOURCE( IDC_SIZEALL ) );
				}

				break;
			}
			case WM_SIZE:
			{
				RECT Rect;

				if( m_pChildWindow[ 0 ] )
				{
					if( m_SplitType == SPLIT_TYPE_HORIZONTAL )
					{
						MoveWindow( m_pChildWindow[ 0 ]->GetWindowHandle( ), 0, 0,
							LOWORD( p_LongParam ), m_SplitterPosition.y - 1, TRUE );
					}
					else if( m_SplitType == SPLIT_TYPE_VERTICAL )
					{
						MoveWindow( m_pChildWindow[ 0 ]->GetWindowHandle( ), 0, 0,
							m_SplitterPosition.x - 1, HIWORD( p_LongParam ), TRUE );
					}
					else
					{
						// Top-left
						MoveWindow( m_pChildWindow[ 0 ]->GetWindowHandle( ), 0, 0,
							m_SplitterPosition.x - 1, m_SplitterPosition.y - 1, TRUE );
					}
				}

				if( m_pChildWindow[ 1 ] )
				{
					if( m_SplitType == SPLIT_TYPE_HORIZONTAL )
					{
						MoveWindow( m_pChildWindow[ 1 ]->GetWindowHandle( ), 0,
							m_SplitterPosition.y + 1, LOWORD( p_LongParam ),
							HIWORD( p_LongParam ) - m_SplitterPosition.y - 2, TRUE );
					}
					else if( m_SplitType == SPLIT_TYPE_VERTICAL )
					{
						MoveWindow( m_pChildWindow[ 1 ]->GetWindowHandle( ),
							m_SplitterPosition.x + 1, 0,
							LOWORD( p_LongParam ) - m_SplitterPosition.x - 2,
							HIWORD( p_LongParam ), TRUE );
					}
					else
					{
						// Top-right
						MoveWindow( m_pChildWindow[ 1 ]->GetWindowHandle( ),
							m_SplitterPosition.x + 2, 0,
							LOWORD( p_LongParam ) - ( m_SplitterPosition.x - 1 ),
							m_SplitterPosition.y - 1, TRUE );
					}
				}

				if( m_pChildWindow[ 2 ] )
				{
					// Bottom-right
					MoveWindow( m_pChildWindow[ 2 ]->GetWindowHandle( ),
						m_SplitterPosition.x + 2, m_SplitterPosition.y + 2,
						LOWORD( p_LongParam ) - ( m_SplitterPosition.x - 1 ),
						HIWORD( p_LongParam ) - ( m_SplitterPosition.y - 1 ), TRUE );
				}

				if( m_pChildWindow[ 3 ] )
				{
					// Bottom-left
					MoveWindow( m_pChildWindow[ 3 ]->GetWindowHandle( ),
						0, m_SplitterPosition.y + 2,
						m_SplitterPosition.x - 1,
						HIWORD( p_LongParam ) - ( m_SplitterPosition.y - 1 ), TRUE );
				}

				break;
			}
			case WM_MOUSEMOVE:
			{
				if( m_SplitType == SPLIT_TYPE_FOUR_WAY )
				{
					POINTS Cursor = MAKEPOINTS( p_LongParam );
					
					if( ( Cursor.x > m_SplitterPosition.x - 10 ) &&
						( Cursor.x < m_SplitterPosition.x + 10 ) )
					{
						if( ( m_SplitterMoving && m_SplitterMoveHorizontal ) ||
							( !m_SplitterMoving ) )
						{
							SetCursor( m_CursorWE );
						}
					}
					else if( ( Cursor.y > m_SplitterPosition.y - 10 ) &&
						( Cursor.y < m_SplitterPosition.y + 10 ) )
					{
						if( ( m_SplitterMoving && m_SplitterMoveVertical ) ||
							( !m_SplitterMoving ) )
						{
							SetCursor( m_CursorNS );
						}
					}
					if( ( Cursor.x > m_SplitterPosition.x - 10 ) &&
						( Cursor.x < m_SplitterPosition.x + 10 ) &&
						( Cursor.y > m_SplitterPosition.y - 10 ) &&
						( Cursor.y < m_SplitterPosition.y + 10 ) )
					{
						if( ( m_SplitterMoveHorizontal ==
								m_SplitterMoveVertical ) ||
							( !m_SplitterMoving ) )
						{
							SetCursor( m_Cursor );
						}
					}
				}			

				if( ( p_WordParam == MK_LBUTTON ) && m_SplitterMoving )
				{
					RECT Rect;
					GetClientRect( m_WindowHandle, &Rect );

					if( m_SplitType == SPLIT_TYPE_HORIZONTAL )
					{
						if( HIWORD( p_LongParam ) > Rect.bottom )
						{
							return 0L;
						}
						m_SplitterPosition.y = HIWORD( p_LongParam );
					}
					else if( m_SplitType == SPLIT_TYPE_VERTICAL )
					{
						if( LOWORD( p_LongParam ) > Rect.right )
						{
							return 0L;
						}

						m_SplitterPosition.x = LOWORD( p_LongParam );
					}
					else
					{
						if( HIWORD( p_LongParam ) > Rect.bottom )
						{
							return 0L;
						}
						if( LOWORD( p_LongParam ) > Rect.right )
						{
							return 0L;
						}

						POINTS Cursor = MAKEPOINTS( p_LongParam );
				
						if( m_SplitterMoveHorizontal )
						{
							m_SplitterPosition.x = LOWORD( p_LongParam );
						}
						else if( m_SplitterMoveVertical )
						{
							m_SplitterPosition.y = HIWORD( p_LongParam );								
						}
						
						if( m_SplitterMoveVertical &&
							m_SplitterMoveHorizontal )
						{
							SetCursor( m_Cursor );
							m_SplitterPosition.x = LOWORD( p_LongParam );
							m_SplitterPosition.y = HIWORD( p_LongParam );
						}
					}

					SendMessage( m_WindowHandle, WM_SIZE, 0,
						MAKELPARAM( Rect.right, Rect.bottom ) );
				}

				break;
			}
			case WM_LBUTTONDOWN:
			{
				if( m_SplitterMoving == false )
				{
					if( m_SplitType == SPLIT_TYPE_FOUR_WAY )
					{
						POINTS Cursor = MAKEPOINTS( p_LongParam );
						
						if( ( Cursor.x > m_SplitterPosition.x - 10 ) &&
							( Cursor.x < m_SplitterPosition.x + 10 ) )
						{
							SetCursor( m_CursorWE );
							m_SplitterMoveHorizontal = true;
							m_SplitterMoveVertical = false;
						}
						else if( ( Cursor.y > m_SplitterPosition.y - 10 ) &&
							( Cursor.y < m_SplitterPosition.y + 10 ) )
						{						
							SetCursor( m_CursorNS );
							m_SplitterMoveVertical = true;
							m_SplitterMoveHorizontal = false;
						}

						if( ( Cursor.x > m_SplitterPosition.x - 10 ) &&
							( Cursor.x < m_SplitterPosition.x + 10 ) &&
							( Cursor.y > m_SplitterPosition.y - 10 ) &&
							( Cursor.y < m_SplitterPosition.y + 10 ) )
						{
							SetCursor( m_Cursor );
							m_SplitterMoveVertical = true;
							m_SplitterMoveHorizontal = true;
						}
					}
					else
					{
						SetCursor( m_Cursor );
						m_SplitterMoveVertical = true;
						m_SplitterMoveHorizontal = true;
					}
					m_SplitterMoving = true;
				}
				SetCapture( m_WindowHandle );

				break;
			}
			case WM_LBUTTONUP:
			{
				ReleaseCapture( );
				m_SplitterMoving = false;

				break;
			}
			default:
			{
				return DefWindowProc( m_WindowHandle, p_Message, p_WordParam,
					p_LongParam );
			}
		}

		return 0L;
	}

	LRESULT CALLBACK WindowSplitter::InitialWindowProc(	HWND p_WindowHandle,
		UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam )
	{
		if( p_Message == WM_NCCREATE )
		{
			LPCREATESTRUCT CreateStruct =
				reinterpret_cast< LPCREATESTRUCT >( p_LongParam );
			void *pCreateParam = CreateStruct->lpCreateParams;
			WindowSplitter *pThis =
				reinterpret_cast< WindowSplitter * >( pCreateParam );
			pThis->m_WindowHandle = p_WindowHandle;
			
			SetWindowLongPtr( pThis->m_WindowHandle, GWLP_USERDATA,
				reinterpret_cast< LONG_PTR >( pThis ) );
			SetWindowLongPtr( pThis->m_WindowHandle, GWLP_WNDPROC,
				reinterpret_cast< LONG_PTR >(
					&WindowSplitter::StaticWindowProc ) );

			return pThis->WindowProc( p_Message, p_WordParam, p_LongParam );
		}

		return DefWindowProc( p_WindowHandle, p_Message, p_WordParam,
			p_LongParam );
	}

	LRESULT CALLBACK WindowSplitter::StaticWindowProc( HWND p_WindowHandle,
		UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam )
	{
		LONG_PTR UserData = GetWindowLongPtr( p_WindowHandle, GWLP_USERDATA );
		WindowSplitter *pThis =
			reinterpret_cast< WindowSplitter * >( UserData );

		assert( pThis );
		assert( p_WindowHandle == pThis->m_WindowHandle );

		return pThis->WindowProc( p_Message, p_WordParam, p_LongParam );
	}

	int WindowSplitter::CreateSplitter( )
	{
		if( m_ParentWindow == NULL )
		{
			MessageBox( NULL, "Splitter parent not set", "TERMED",
				MB_OK | MB_ICONERROR );

			return 1;
		}

		m_WindowHandle = CreateWindowEx( WS_EX_CLIENTEDGE, "TERMED | SPLITTER",
			NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, 0, 0,
			m_ParentWindow, NULL, GetModuleHandle( NULL ), this );

		return 0;
	}
}
