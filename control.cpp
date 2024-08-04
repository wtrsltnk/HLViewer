#include "control.h"
#include <iostream>

using namespace ui;

Control::Control(LPTSTR windowClass, DWORD id)
        : wnd(windowClass, id), m_parent(NULL)
{
}

Control::~Control()
{
}

void Control::createControl(Window* parent)
{
    m_parent = parent;
    
    if (parent == NULL)
	this->m_hParent = HWND_DESKTOP;
    else
        this->m_hParent = parent->getHandle();
    
    this->m_hWnd = ::CreateWindowEx(this->m_exStyle,
                        this->m_strWindowClass,
                        this->m_strWindowTitle,
                        this->m_style,
                        this->m_x, this->m_y,
                        this->m_width, this->m_height,
                        (HWND) this->m_hParent,
                        (HMENU) this->m_id,
                        ::GetModuleHandle(NULL), 
                        NULL);
    
    ::ShowWindow(this->m_hWnd, SW_SHOWNORMAL);
}
