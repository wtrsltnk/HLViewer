
/* 
 * File:   dialog.cpp
 * Author: Wouter
 * 
 * Created on February 14, 2009, 11:26 AM
 */

#include "dialog.h"
#include <stdio.h>
#include <iostream>

using namespace ui;

Dialog::Dialog(LPTSTR windowClass)
        : Window(windowClass), m_done(false)
{
}

Dialog::~Dialog()
{
}

bool Dialog::showModal(Window* parent)
{
    if (parent == NULL)
	throw ("A modal dialog needs a parent window");

    if (this->show(parent))
    {
        EnableWindow(parent->getHandle(), FALSE);

	this->onInitializeDialog();
	
        MSG msg;
        for( ; !this->m_done; WaitMessage())
        {
            while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                if(!IsDialogMessage(parent->getHandle(), &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }

        DestroyWindow(this->m_hWnd);
	EnableWindow(parent->getHandle(), TRUE);
	SendMessage(parent->getHandle(), WM_SETFOCUS, 0, 0);
	SetForegroundWindow(parent->getHandle());
	
	
    }

    return true;
}

LRESULT Dialog::objectProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE:
        {
            EnableWindow(m_hParent, TRUE);
            SendMessage(m_hParent, WM_SETFOCUS, 0, 0);
            SetForegroundWindow(m_hParent);
            this->m_done = true;
            break;
        }
    }
    return DefWindowProc(this->m_hWnd, msg, wParam, lParam);
}
