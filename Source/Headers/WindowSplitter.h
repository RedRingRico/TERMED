#ifndef __TERMED_WINDOWSPLITTER_H__
#define __TERMED_WINDOWSPLITTER_H__

#include <EditorWindow.h>

namespace TERMED
{
	enum SPLIT_TYPE
	{
		SPLIT_TYPE_HORIZONTAL,
		SPLIT_TYPE_VERTICAL,
		SPLIT_TYPE_FOUR_WAY
	};

	class WindowSplitter : public EditorWindow
	{
	public:
		explicit WindowSplitter( SPLIT_TYPE p_SplitType );
		virtual ~WindowSplitter( );

		virtual void SetDeviceContext( HDC p_DeviceContext );
		virtual void SetParentWindow( HWND p_ParentWindow );

		int SetWindow( size_t p_Index, EditorWindow *p_pWindow );

		void CentreSplitter( );

		static int RegisterWindow( );
		static void UnregisterWindow( );

	private:
		LRESULT CALLBACK WindowProc( UINT p_Message, WPARAM p_WordParam,
			LPARAM p_LongParam );

		static LRESULT CALLBACK InitialWindowProc( HWND p_WindowHandle,
			UINT p_Message, WPARAM p_WordParam, LPARAM p_LongParam );

		static LRESULT CALLBACK StaticWindowProc( HWND p_WindowHandle,
			UINT p_Message, WPARAM p_WordPara, LPARAM p_LongParam );

		int CreateSplitter( );

		SPLIT_TYPE		m_SplitType;
		EditorWindow	*m_pChildWindow[ 4 ];
		POINT			m_SplitterPosition;
		bool			m_SplitterMoving;
		bool			m_SplitterMoveHorizontal;
		bool			m_SplitterMoveVertical;
		HCURSOR			m_Cursor;
		HCURSOR			m_CursorNS;
		HCURSOR			m_CursorWE;
	};
}

#endif // __TERMED_WINDOWSPLITTER_H__
