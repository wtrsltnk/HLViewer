/*
 * File:   Window.h
 * Author: Wouter
 *
 * Created on June 27, 2008, 12:27 AM
 */

#ifndef WINDOW_IMP_H_
#define WINDOW_IMP_H_

#include "wnd.h"

namespace ui
{
    class Window : public wnd
    {
    private:
	static LRESULT staticProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    protected:
	HICON m_hIcon;
	HICON m_hCursor;
	HMENU m_hMenu;
	HBRUSH m_hBackgroundColor;

	bool registerClass();
	virtual LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

    public:
	Window(LPTSTR windowClass);
	virtual ~Window();

	bool show(Window* parent = NULL);
	int runApplication();
    };
}

#endif /*WINDOW_IMP_H_*/
