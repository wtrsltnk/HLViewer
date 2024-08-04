/* 
 * File:   miptexbasedfile.h
 * Author: Administrator
 *
 * Created on March 13, 2009, 11:53 AM
 */

#ifndef _MIPTEXBASEDFILE_H
#define	_MIPTEXBASEDFILE_H

#include "texturecontainer.h"

typedef struct sBSPMipTexOffsetTable
{
    int miptexCount;
    int offsets[1];             /* an array with "miptexcount" number of offsets */

} tBSPMipTexOffsetTable;

typedef struct sBSPMipTexHeader
{
    char name[16];
    unsigned int width;
    unsigned int height;
    unsigned int offsets[4];

} tBSPMipTexHeader;

class MiptexBasedFile : public TextureContainer
{
public:
    MiptexBasedFile();
    virtual ~MiptexBasedFile();

protected:
    void createTextureFromMiptex(unsigned char* data, bool blueIsInvisible = false);

};

#endif	/* _MIPTEXBASEDFILE_H */

