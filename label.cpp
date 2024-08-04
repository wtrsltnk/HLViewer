/* 
 * File:   label.cpp
 * Author: Wouter
 * 
 * Created on February 25, 2009, 7:58 AM
 */

#include "label.h"

using namespace ui;

Label::Label()
	: Control("Static")
{
}

Label::Label(DWORD id)
	: Control("Static", id)
{
}

Label::~Label()
{
}

