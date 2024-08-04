/* 
 * File:   wadfile.h
 * Author: Wouter
 *
 * Created on January 24, 2009, 3:54 PM
 */

#ifndef _WADFILE_H
#define	_WADFILE_H

#include "Common/string.h"
#include <stdio.h>
#include "containerfile.h"
#include "miptexbasedfile.h"

#define HL1_WAD_SIGNATURE "WAD3"
#define	MAX_MIP_LEVELS 4

typedef struct sWADHeader
{
    char signature[4];
    int lumpsCount;
    int lumpsOffset;

} tWADHeader;

typedef struct sWADLump
{
    int offset;
    int sizeOnDisk;
    int size;
    char type;
    char compression;
    char empty0;
    char empty1;
    char name[16];

} tWADLump;

class WadFile : public ContainerFile, public MiptexBasedFile
{
public:
    WadFile();
    virtual ~WadFile();

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
    tWADHeader m_header;
    tWADLump* m_lumps;
    GLuint* m_textureIndex;

    void createTexture(tWADLump& lump, bool blueIsInvisible = false);
};

#endif	/* _WADFILE_H */

