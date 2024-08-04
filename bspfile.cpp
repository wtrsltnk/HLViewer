/* 
 * File:   bspfile.cpp
 * Author: Wouter
 * 
 * Created on January 25, 2009, 10:36 PM
 */

#include "bspfile.h"

BspFile::BspFile()
        : m_data(0), m_miptexCount(0), m_miptexIndex(0), m_textureIndex(0)
{
}

BspFile::~BspFile()
{
    this->closeFile();
}

bool BspFile::postOpenFile()
{
    bool result = false;
    fread(&this->m_header, 1, sizeof(tBSPHeader), this->m_file);

    if (this->m_header.signature == HL1_BSP_SIGNATURE)
    {
        if (this->m_header.lumps[HL1_BSP_TEXTURELUMP].size > 0)
        {
            this->m_miptexCount = 0;

            this->m_data = new unsigned char[this->m_header.lumps[HL1_BSP_TEXTURELUMP].size];
            // First read the number of miptexes in this BSP file
            fseek(this->m_file, this->m_header.lumps[HL1_BSP_TEXTURELUMP].offset, SEEK_SET);
            fread(this->m_data, 1, this->m_header.lumps[HL1_BSP_TEXTURELUMP].size, this->m_file);

            int tmpCount = (int)*this->m_data;
            int* tmpIndex = 0;

            if (tmpCount > 0)
            {
                // Read all the offsets for the miptexes
                tmpIndex = new int[tmpCount];
                fseek(this->m_file, this->m_header.lumps[HL1_BSP_TEXTURELUMP].offset + sizeof(int), SEEK_SET);
                fread(tmpIndex, tmpCount, sizeof(int), this->m_file);

                // Count all the Miptexes contianed in the BSP file (the ones with offset larger then 0)
                for (int i = 0; i < tmpCount; i++)
                {
                    tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)(this->m_data + tmpIndex[i]);
                    if (miptex->offsets[0] != 0)
                        this->m_miptexCount++;
                }

                if (this->m_miptexCount > 0)
                {
                    this->m_miptexIndex = new int[this->m_miptexCount];
                    this->m_textureIndex = new GLuint[this->m_miptexCount];

                    // Copy all the containing BSP offsets
                    for (int i = 0, j = 0; i < tmpCount; i++)
                    {
                        tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)(this->m_data + tmpIndex[i]);
                        if (miptex->offsets[0] != 0)
                            this->m_miptexIndex[j++] = tmpIndex[i];
                    }
                    result = true;
                }
                else
                {
                    fclose(this->m_file);
                    this->m_file = 0;
                    this->addError("There are no textures in this BSP file");
                }
                delete []tmpIndex;
            }
            else
            {
                fclose(this->m_file);
                this->m_file = 0;
                this->addError("There are no textures in this BSP file");
            }
        }
    }
    else
    {
        fclose(this->m_file);
        this->m_file = 0;
        this->addError("This is no BSP file");
    }
    return result;
}

void BspFile::preCloseFile()
{
    if (this->m_data != 0)
        delete []this->m_data;
    this->m_data = 0;

    if (this->m_miptexIndex != 0)
        delete []this->m_miptexIndex;
    this->m_miptexIndex = 0;

    if (this->m_textureIndex != 0)
        delete []this->m_textureIndex;
    this->m_textureIndex = 0;
}

Container* BspFile::getContainer(int type)
{
    switch (type)
    {
        case eTextureContainer:
            return (Container*)this;
    }
    return 0;
}

String BspFile::getFileName() const
{
    return this->m_filename;
}

int BspFile::getTextureCount() const
{
    if (this->m_file != 0)
    {
        return this->m_miptexCount;
    }
    return 0;
}

String BspFile::getTextureName(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_miptexCount)
        {
            tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)(this->m_data + this->m_miptexIndex[index]);
            return miptex->name;
        }
    }
    return "";
}

GLuint BspFile::getTextureID(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_miptexCount)
        {
            return this->m_textureIndex[index];
        }
    }
    return 0;
}

void BspFile::getTextureSize(int index, int& width, int& height) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_miptexCount)
        {
            tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)(this->m_data + this->m_miptexIndex[index]);
            width = miptex->width;
            height = miptex->height;
        }
    }
}

GLuint BspFile::setupTextureToGl(int index)
{
    GLuint id = 0;

    if (index >= 0 && index < this->m_miptexCount)
    {
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	this->createTextureFromMiptex(this->m_data + this->m_miptexIndex[index]);
    }
    return id;
}

void BspFile::cleanupTextureFromGl(GLuint id)
{
    if (this->m_file != 0)
    {
	glDeleteTextures(1, &id);
    }
}

void BspFile::setupTextures()
{
    if (this->m_file != 0)
    {
        glGenTextures(this->m_miptexCount, this->m_textureIndex);
        for (int i = 0; i < this->m_miptexCount; i++)
        {
            glBindTexture(GL_TEXTURE_2D, this->m_textureIndex[i]);
            this->createTextureFromMiptex(this->m_data + this->m_miptexIndex[i]);
        }
    }
}

void BspFile::cleanupTextures()
{
    if (this->m_file != 0)
    {
	glDeleteTextures(this->m_miptexCount, this->m_textureIndex);
    }
}


