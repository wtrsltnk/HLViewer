/*
 * File:   window.cpp
 * Author: Wouter
 *
 * Created on February 25, 2009, 7:58 AM
 */

#include "window.h"

using namespace ui;

Window::Window(LPTSTR windowClass)
	: wnd(windowClass)
{
    this->m_strWindowTitle = "DefaultWindow";
    this->m_exStyle = WS_EX_CLIENTEDGE;
    this->m_style = WS_OVERLAPPEDWINDOW;
    this->m_x = CW_USEDEFAULT;
    this->m_y = CW_USEDEFAULT;
    this->m_width = CW_USEDEFAULT;
    this->m_height = CW_USEDEFAULT;
    this->m_hIcon = ::LoadIcon((HINSTANCE) NULL, IDI_APPLICATION);
    this->m_hCursor = ::LoadCursor((HINSTANCE) NULL, IDC_ARROW);
    this->m_hMenu = NULL;
    this->m_hBackgroundColor = (HBRUSH)(COLOR_WINDOW);
}

Window::~Window()
{
}

bool Window::show(Window* parent)
{
    if (parent == NULL)
	this->m_hParent = HWND_DESKTOP;
    else
        this->m_hParent = parent->m_hWnd;

    if (this->registerClass() == true)
    {
        this->m_hWnd = CreateWindowEx(this->m_exStyle,
                                    this->m_strWindowClass,
                                    this->m_strWindowTitle,
                                    this->m_style,
                                    this->m_x,
                                    this->m_y,
                                    this->m_width,
                                    this->m_height,
                                    (HWND) this->m_hParent,
                                    (HMENU) this->m_hMenu,
                                    ::GetModuleHandle(NULL), 
                                    (LPVOID) this); 

        if (this->m_hWnd)
        {
            ::ShowWindow(this->m_hWnd, SW_SHOW);
            ::UpdateWindow(this->m_hWnd);
            return true;
        }
    }
    return false;
}

int Window::runApplication()
{
    MSG msg;
    BOOL bRet;

    if (this->show())
    {
        while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
        {
            if (bRet == -1)
            {
                DWORD error = ::GetLastError();
                        // Check error codes op:
                        // http://msdn2.microsoft.com/en-us/library/ms681381.aspx

                return error;
            }
            else
            {
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
        }

        return msg.wParam;
    }
    return 0;
}

bool Window::registerClass()
{
    WNDCLASS wc;

    if (GetClassInfo(::GetModuleHandle(NULL), this->m_strWindowClass, &wc) == 0)
    {
        wc.style = 0; 
        wc.lpfnWndProc = (WNDPROC)Window::staticProc;
        wc.cbClsExtra = 0; 
        wc.cbWndExtra = 0; 
        wc.hInstance = ::GetModuleHandle(NULL); 
        wc.hIcon = this->m_hIcon;
        wc.hCursor = this->m_hCursor;
        wc.hbrBackground = this->m_hBackgroundColor;
        wc.lpszMenuName =  "MainMenu"; 
        wc.lpszClassName = this->m_strWindowClass;

        if (!::RegisterClass(&wc))
            return false; 
    }
    return true;
}

LRESULT Window::staticProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = NULL;

    if (msg == WM_NCCREATE)
    {
        window = reinterpret_cast <Window*> (((LPCREATESTRUCT)lParam)->lpCreateParams);

        if (window != NULL)
        {
            window->m_hWnd = hWnd;

            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast <long long> (window));

            return window->objectProc(msg, wParam, lParam);
        }
    }
    else
    {
        window = reinterpret_cast <Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if (window != NULL)
        {
            return window->objectProc(msg, wParam, lParam);
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
