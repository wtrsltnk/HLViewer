/*
 * File:   wnd.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 2:48 PM
 */

#ifndef _WND_IMP_H
#define _WND_IMP_H

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

        HWND operator*();
        HWND getHandle() const;

    protected:
        HWND m_hWnd = nullptr;
        HWND m_hParent = nullptr;
        DWORD m_id = 0;
        DWORD m_style = 0, m_exStyle = 0;
        int m_x = 0, m_y = 0, m_width = 1, m_height = 1;
        LPTSTR m_strWindowClass = nullptr, m_strWindowTitle = nullptr;
    };
} // namespace ui

#endif /* _WND_IMP_H */
