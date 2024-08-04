/* 
 * File:   wadfile.cpp
 * Author: Wouter
 * 
 * Created on January 24, 2009, 3:54 PM
 */

#include "wadfile.h"

WadFile::WadFile()
        : m_lumps(0), m_textureIndex(0)
{
}

WadFile::~WadFile()
{
    this->closeFile();
}

bool WadFile::postOpenFile()
{
    bool result = false;
    
    fread(&this->m_header, 1, sizeof(tWADHeader), this->m_file);

    if (strncmp(this->m_header.signature, "WAD3", 4) == 0)
    {
        this->m_lumps = new tWADLump[this->m_header.lumpsCount];
        this->m_textureIndex = new GLuint[this->m_header.lumpsCount];

        fseek(this->m_file, this->m_header.lumpsOffset, SEEK_SET);
        fread(this->m_lumps, this->m_header.lumpsCount, sizeof(tWADLump), this->m_file);

        result = true;
    }
    else
    {
        fclose(this->m_file);
        this->m_file = 0;
        this->addError("This is no WAD file");
    }
    return result;
}

void WadFile::preCloseFile()
{
    if (this->m_lumps != 0)
        delete []this->m_lumps;
    this->m_lumps = 0;

    if (this->m_textureIndex != 0)
        delete []this->m_textureIndex;
    this->m_textureIndex = 0;

    if (this->m_file != false)
        fclose(this->m_file);
    this->m_file = 0;
}

Container* WadFile::getContainer(int type)
{
    switch (type)
    {
        case eTextureContainer:
            return (Container*)this;
    }
    return 0;
}

String WadFile::getFileName() const
{
    return this->m_filename;
}

int WadFile::getTextureCount() const
{
    if (this->m_file != 0)
    {
        return this->m_header.lumpsCount;
    }
    return 0;
}

String WadFile::getTextureName(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.lumpsCount)
        {
            return this->m_lumps[index].name;
        }
    }
    return "";
}
GLuint WadFile::getTextureID(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.lumpsCount)
        {
            return this->m_textureIndex[index];
        }
    }
    return 0;
}

void WadFile::getTextureSize(int index, int& width, int& height) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.lumpsCount)
        {
            unsigned char* data = new unsigned char[this->m_lumps[index].size];
            fseek(this->m_file, this->m_lumps[index].offset, SEEK_SET);
            fread(data, 1, this->m_lumps[index].size, this->m_file);

            tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)data;
            width = miptex->width;
            height = miptex->height;
            delete []data;
        }
    }
}

GLuint WadFile::setupTextureToGl(int index)
{
    GLuint id = 0;

    if (index >= 0 && index < this->m_header.lumpsCount)
    {
        glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	this->createTexture(this->m_lumps[index]);
    }
    return id;
}

void WadFile::cleanupTextureFromGl(GLuint id)
{
    if (this->m_file != 0)
    {
	glDeleteTextures(1, &id);
    }
}

void WadFile::setupTextures()
{
    if (this->m_file != 0)
    {
        glGenTextures(this->m_header.lumpsCount, this->m_textureIndex);
        for (int i = 0; i < this->m_header.lumpsCount; i++)
        {
            glBindTexture(GL_TEXTURE_2D, this->m_textureIndex[i]);
            this->createTexture(this->m_lumps[i]);
        }
    }
}

void WadFile::cleanupTextures()
{
    if (this->m_file != 0)
    {
	glDeleteTextures(this->m_header.lumpsCount, this->m_textureIndex);
    }
}

void WadFile::createTexture(tWADLump& lump, bool blueIsInvisible)
{
    unsigned char* data = new unsigned char[lump.size];
    fseek(this->m_file, lump.offset, SEEK_SET);
    fread(data, 1, lump.size, this->m_file);

    this->createTextureFromMiptex(data, blueIsInvisible);
    
    delete []data;
}

