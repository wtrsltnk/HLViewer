/* 
 * File:   containerfile.h
 * Author: Wouter
 *
 * Created on October 28, 2009, 6:10 PM
 */

#ifndef _CONTAINERFILE_H
#define	_CONTAINERFILE_H

#include "basefile.h"
#include "error.h"

enum
{
    eTextureContainer = 1
};

class Container : public Error
{
public:
    virtual ~Container() { }

    virtual int getType() = 0;
    virtual String getTitle() = 0;

};

class ContainerFile : public BaseFile
{
public:
    virtual ~ContainerFile() { }

    virtual Container* getContainer(int type) = 0;
};

#endif	/* _CONTAINERFILE_H */

