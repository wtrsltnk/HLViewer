/* 
 * File:   mdlfile.h
 * Author: Wouter
 *
 * Created on January 28, 2009, 4:29 PM
 */

#ifndef _MDLFILE_H
#define	_MDLFILE_H

#include "Common/string.h"
#include <stdio.h>
#include "containerfile.h"
#include "texturecontainer.h"

#define MDL_SIGNATURE (('T' << 24) | ('S' << 16) | ('D' << 8) | 'I')
#define MDL_SEQUENCE_SIGNATURE (('Q' << 24) | ('S' << 16) | ('D' << 8) | 'I')

typedef struct sMDLHeader
{
    int id;
    int version;

    char name[64];
    int length;

    float eyeposition[3];
    float min[3]; float max[3];

    float bbmin[3]; float bbmax[3];

    int flags;

    int boneCount;              int firstBoneOffset;
    int boneControllerCount;    int firstBoneControllerOffset;
    int hitboxCount;            int firstHitboxOffset;
    int sequenceCount;          int firstSequenceOffset;
    int sequenceGroupCount;     int firstSequenceGroupOffset;
    int textureCount;           int firstTextureOffset;             int textureDataOffset;
    int	skinReferenceCount;     int skinFamilieCount;               int firstSkinOffset;
    int bodypartCount;          int firstBodypartOffset;
    int attachmentCount;        int firstAttachmentOffset;
    int soundTable;             int soundOffset;                    int soundGroups;                int soundGroupOffset;
    int transitionCount;        int firstTransitionOffset;

} tMDLHeader;

typedef struct sMDLTexture
{
    char name[64];
    int flags;
    int width;
    int height;
    int index;

} tMDLTexture;

class MdlFile : public ContainerFile, public TextureContainer
{
public:
    MdlFile();
    virtual ~MdlFile();

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
    tMDLHeader m_header;
    tMDLTexture* m_textures;
    GLuint* m_textureIndex;

};

#endif	/* _MDLFILE_H */

