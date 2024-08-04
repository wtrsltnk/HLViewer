/*
 * File:   button.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 7:54 AM
 */

#ifndef _BUTTON_IMP_H
#define _BUTTON_IMP_H

#include "control.h"

namespace ui
{
    class Button : public Control
    {
    public:
        Button();
        Button(DWORD id);
        virtual ~Button();

    private:
    };
} // namespace ui

#endif /* _BUTTON_IMP_H */
