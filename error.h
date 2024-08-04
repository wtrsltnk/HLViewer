/*
 * File:   error.h
 * Author: Wouter
 *
 * Created on January 24, 2009, 4:41 PM
 */

#ifndef _ERROR_H
#define _ERROR_H

#include "Common/string.h"

class Error
{
public:
    Error();
    virtual ~Error();

    String getLastError() const;
    bool hasError() const;

protected:
    void addError(String error);

private:
    bool m_hasError = false;
    char m_lastError[256];
};

#endif /* _ERROR_H */
