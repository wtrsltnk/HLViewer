/* 
 * File:   button.cpp
 * Author: Administrator
 * 
 * Created on February 25, 2009, 7:54 AM
 */

#include "button.h"

using namespace ui;

Button::Button()
	: Control("Button")
{
}

Button::Button(DWORD id)
	: Control("Button", id)
{
}

Button::~Button()
{
}

