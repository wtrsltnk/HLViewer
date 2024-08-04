/* 
 * File:   texturecontainer.h
 * Author: Wouter
 *
 * Created on January 25, 2009, 10:10 PM
 */

#ifndef _TEXTURECONTAINER_H
#define	_TEXTURECONTAINER_H

#include "Common/common.h"
#include "containerfile.h"
#include <glad/glad.h>

class TextureContainer : public Container
{
public:
    virtual ~TextureContainer() { }

    virtual int getType() { return eTextureContainer; }
    virtual String getTitle() { return "textures"; }

    virtual String getFileName() const = 0;
    virtual int getTextureCount() const = 0;
    virtual String getTextureName(int index) const = 0;
    virtual GLuint getTextureID(int index) const = 0;
    virtual void getTextureSize(int index, int& width, int& height) const = 0;
    virtual GLuint setupTextureToGl(int index) = 0;
    virtual void setupTextures() = 0;
    virtual void cleanupTextureFromGl(GLuint id) = 0;
    virtual void cleanupTextures() = 0;

};

#endif	/* _TEXTURECONTAINER_H */

