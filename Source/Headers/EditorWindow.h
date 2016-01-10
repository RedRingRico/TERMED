#ifndef __TERMED_EDITORWINDOW_H__
#define __TERMED_EDITORWINDOW_H__

#include <windows.h>

namespace TERMED
{
	class EditorWindow
	{
	public:
		virtual ~EditorWindow( );

		virtual void SetDeviceContext( HDC p_DeviceContext );
		virtual void SetParentWindow( HWND p_ParentWindow );

		HWND GetWindowHandle( );

	protected:
		HWND	m_ParentWindow;
		HWND	m_WindowHandle;
		HDC		m_DeviceContext;		
	};
}

#endif // __TERMED_EDITORWINDOW_H__
