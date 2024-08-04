/* 
 * File:   label.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 7:58 AM
 */

#ifndef _LABEL_IMP_H
#define	_LABEL_IMP_H

#include "control.h"

namespace ui
{
    class Label : public Control
    {
    public:
	Label();
	Label(DWORD id);
	virtual ~Label();

    private:

    };
}

#endif	/* _LABEL_IMP_H */

