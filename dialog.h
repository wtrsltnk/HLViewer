/*
 * File:   dialog.h
 * Author: Wouter
 *
 * Created on February 14, 2009, 11:26 AM
 */

#ifndef _DIALOG_IMP_H
#define _DIALOG_IMP_H

#include "window.h"

namespace ui
{
    class Dialog : protected Window
    {
    public:
        Dialog(LPTSTR windowClass);
        virtual ~Dialog();

        bool showModal(Window *parent);

    protected:
        virtual LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);
        virtual void onInitializeDialog() = 0;

    private:
        bool m_done = false;
    };
} // namespace ui

#endif /* _DIALOG_IMP_H */
