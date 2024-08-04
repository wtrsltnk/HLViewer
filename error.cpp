/* 
 * File:   error.cpp
 * Author: Wouter
 * 
 * Created on January 24, 2009, 4:41 PM
 */

#include "error.h"

Error::Error()
        : m_hasError(false)
{
}

Error::~Error()
{
}

String Error::getLastError() const
{
    return this->m_lastError;
}

bool Error::hasError() const
{
    return this->m_hasError;
}

void Error::addError(String error)
{
    this->m_hasError = true;
    strcpy(this->m_lastError, error);
}

