/* 
 * File:   wnd.cpp
 * Author: Administrator
 * 
 * Created on February 25, 2009, 2:48 PM
 */

#include "wnd.h"

using namespace ui;

wnd::wnd(LPTSTR windowClass, DWORD id)
        : m_hWnd(0), m_hParent(0), m_id(id), m_style(WS_CHILD), m_exStyle(WS_EX_WINDOWEDGE), m_x(0), m_y(0), m_width(100), m_height(100), m_strWindowClass(windowClass), m_strWindowTitle("")
{
}

wnd::~wnd()
{
}

void wnd::move(int x, int y)
{
    this->m_x = x;
    this->m_y = y;

    ::MoveWindow(this->m_hWnd, this->m_x, this->m_y, this->m_width, this->m_height, TRUE);
}

void wnd::resize(int width, int height)
{
    this->m_width = width;
    this->m_height = height;

    ::MoveWindow(this->m_hWnd, this->m_x, this->m_y, this->m_width, this->m_height, TRUE);
}

DWORD wnd::getStyle() const
{
    return this->m_style;
}

void wnd::setStyle(DWORD style)
{
    this->m_style = style;
    if (this->m_hWnd != NULL)
        SetWindowLong(this->m_hWnd, GWL_STYLE, this->m_style);
}

DWORD wnd::getExStyle() const
{
    return this->m_exStyle;
}

void wnd::setExStyle(DWORD exStyle)
{
    this->m_exStyle = exStyle;
    if (this->m_hWnd != NULL)
        SetWindowLong(this->m_hWnd, GWL_EXSTYLE, this->m_exStyle);
}

DWORD wnd::getID() const
{
    return this->m_id;
}

void wnd::setID(DWORD id)
{
    this->m_id = id;
    if (this->m_hWnd != NULL)
        SetWindowLong(this->m_hWnd, GWL_ID, this->m_id);
}

LPTSTR wnd::getText() const
{
    return this->m_strWindowTitle;
}

void wnd::setText(LPTSTR text)
{
    this->m_strWindowTitle = text;
    if (this->m_hWnd != NULL)
	SetWindowText(this->m_hWnd, this->m_strWindowTitle);
}

HWND wnd::operator * ()
{
    return this->m_hWnd;
}

HWND wnd::getHandle() const
{
    return this->m_hWnd;
}
