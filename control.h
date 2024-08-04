/* 
 * File:   Control.h
 * Author: Wouter
 *
 * Created on June 27, 2008, 2:49 PM
 */

#ifndef _CONTROL_IMP_H_
#define	_CONTROL_IMP_H_

#include "window.h"

namespace ui
{
    class Control : public wnd
    {
    public:
	Control();
	Control(DWORD id);
	Control(LPTSTR windowClass, DWORD id = 0);
	virtual ~Control();

	virtual void createControl(Window* parent = NULL);

    protected:
	Window* m_parent;
    };
}

#endif	/* _CONTROL_IMP_H_ */

