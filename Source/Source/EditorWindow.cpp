#include <EditorWindow.h>

namespace TERMED
{
	EditorWindow::~EditorWindow( )
	{
		if( m_DeviceContext && m_WindowHandle )
		{
			ReleaseDC( m_WindowHandle, m_DeviceContext );
			DestroyWindow( m_WindowHandle );
		}
	}

	void EditorWindow::SetDeviceContext( HDC p_DeviceContext )
	{
		m_DeviceContext = p_DeviceContext;
	}

	void EditorWindow::SetParentWindow( HWND p_ParentWindow )
	{
		m_ParentWindow = p_ParentWindow;
	}

	HWND EditorWindow::GetWindowHandle( )
	{
		return m_WindowHandle;
	}

	HDC EditorWindow::GetDeviceContext( )
	{
		return m_DeviceContext;
	}
}
