/* 
 * File:   bspfile.h
 * Author: Wouter
 *
 * Created on January 25, 2009, 10:36 PM
 */

#ifndef _BSPFILE_H
#define	_BSPFILE_H

#include "Common/string.h"
#include <stdio.h>
#include "containerfile.h"
#include "miptexbasedfile.h"

#define HL1_BSP_SIGNATURE 30
#define HL1_BSP_LUMPCOUNT 15
#define HL1_BSP_TEXTURELUMP 2

typedef struct sBSPLump
{
    int offset;
    int size;

} tBSPLump;

typedef struct sBSPHeader
{
    int signature;
    tBSPLump lumps[HL1_BSP_LUMPCOUNT];

} tBSPHeader;

class BspFile : public ContainerFile, public MiptexBasedFile
{
public:
    BspFile();
    virtual ~BspFile();

    virtual bool postOpenFile();
    virtual void preCloseFile();

    virtual Container* getContainer(int type);

    virtual String getFileName() const;
    virtual int getTextureCount() const;
    virtual String getTextureName(int index) const;
    virtual GLuint getTextureID(int index) const;
    virtual void getTextureSize(int index, int& width, int& height) const;
    virtual GLuint setupTextureToGl(int index);
    virtual void setupTextures();
    virtual void cleanupTextureFromGl(GLuint id);
    virtual void cleanupTextures();

private:
    tBSPHeader m_header;
    unsigned char* m_data;
    int m_miptexCount;
    int* m_miptexIndex;
    GLuint* m_textureIndex;

};

#endif	/* _BSPFILE_H */

