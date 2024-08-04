/* 
 * File:   basefile.h
 * Author: Administrator
 *
 * Created on March 13, 2009, 6:01 PM
 */

#ifndef _BASEFILE_H
#define	_BASEFILE_H

#include "Common/string.h"
#include <stdio.h>

class BaseFile
{
public:
    BaseFile();
    virtual ~BaseFile();

    bool openFile(String);
    void closeFile();
    
protected:
    virtual bool postOpenFile() { }
    virtual void preCloseFile() { }

    bool readData(char* data, int size, int offset = -1);

protected:
    String m_filename;
    FILE* m_file;
    
};

#endif	/* _BASEFILE_H */

