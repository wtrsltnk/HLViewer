/* 
 * File:   wnd.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 2:48 PM
 */

#ifndef _WND_IMP_H
#define	_WND_IMP_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace ui
{
    class wnd
    {
    public:
	wnd(LPTSTR windowClass, DWORD id = 0);
	virtual ~wnd();

	void move(int x, int y);
	void resize(int width, int height);

	DWORD getStyle() const;
	void setStyle(DWORD style);

	DWORD getExStyle() const;
	void setExStyle(DWORD exStyle);

	DWORD getID() const;
	void setID(DWORD id);

	LPTSTR getText() const;
	void setText(LPTSTR text);

	HWND operator * ();
	HWND getHandle() const;

    protected:
	HWND m_hWnd;
	HWND m_hParent;
	DWORD m_id;
	DWORD m_style, m_exStyle;
	int m_x, m_y, m_width, m_height;
	LPTSTR m_strWindowClass, m_strWindowTitle;

    };
}

#endif	/* _WND_IMP_H */

