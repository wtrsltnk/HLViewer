/* 
 * File:   mdlfile.cpp
 * Author: Wouter
 * 
 * Created on January 28, 2009, 4:29 PM
 */

#include "mdlfile.h"

MdlFile::MdlFile()
        : m_textures(0), m_textureIndex(0)
{
}

MdlFile::~MdlFile()
{
}

bool MdlFile::postOpenFile()
{
    bool result = false;

    fread(&this->m_header, 1, sizeof(tMDLHeader), this->m_file);

    if (this->m_header.id == MDL_SIGNATURE)
    {
        if (this->m_header.textureCount > 0)
        {
            this->m_textures = new tMDLTexture[this->m_header.textureCount];
            this->m_textureIndex = new GLuint[this->m_header.textureCount];

            fseek(this->m_file, this->m_header.firstTextureOffset, SEEK_SET);
            fread(this->m_textures, this->m_header.textureCount, sizeof(tMDLTexture), this->m_file);

            result = true;
        }
        else
        {
            fclose(this->m_file);
            this->m_file = 0;
            this->addError("No textures were found in this MDL file");
        }
    }
    else
    {
        fclose(this->m_file);
        this->m_file = 0;
        if (this->m_header.id == MDL_SEQUENCE_SIGNATURE)
            this->addError("This is a sequence MDL file and does not contain textures");
        else
            this->addError("This is no MDL file");
    }
    return result;
}

void MdlFile::preCloseFile()
{
    if (this->m_textures != 0)
        delete []this->m_textures;
    this->m_textures = 0;

    if (this->m_textureIndex != 0)
        delete []this->m_textureIndex;
    this->m_textureIndex = 0;
}

Container*  MdlFile::getContainer(int type)
{
    switch (type)
    {
        case eTextureContainer:
            return (Container*)this;
    }
    return 0;
}

String MdlFile::getFileName() const
{
    return this->m_filename;
}

int MdlFile::getTextureCount() const
{
    if (this->m_file != 0)
        return this->m_header.textureCount;

    return 0;
}

String MdlFile::getTextureName(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.textureCount)
        {
            return this->m_textures[index].name;
        }
    }
    return "";
}

GLuint MdlFile::getTextureID(int index) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.textureCount)
        {
            return this->m_textureIndex[index];
        }
    }
    return 0;
}

void MdlFile::getTextureSize(int index, int& width, int& height) const
{
    if (this->m_file != 0)
    {
        if (index >= 0 && index < this->m_header.textureCount)
        {
            width = this->m_textures[index].width;
            height = this->m_textures[index].height;
        }
    }
}

GLuint MdlFile::setupTextureToGl(int index)
{
    GLuint id = 0;

    if (index >= 0 && index < this->m_header.textureCount)
    {
        glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int dataSize = this->m_textures[index].width * this->m_textures[index].height;
	int paletteSize = 256 * 3;
	int paletteOffset = this->m_textures[index].index + (this->m_textures[index].width * this->m_textures[index].height);
	unsigned char* data = new unsigned char[dataSize];
	unsigned char* palette = new unsigned char[paletteSize];

	fseek(this->m_file, this->m_textures[index].index, SEEK_SET);
	fread(data, 1, dataSize, this->m_file);

	fseek(this->m_file, paletteOffset, SEEK_SET);
	fread(palette, 1, paletteSize, this->m_file);

	unsigned char* destination = new unsigned char[this->m_textures[index].width * this->m_textures[index].height * 3];
	for (int j = 0; j < dataSize; j++)
	{
	    destination[j*3] = palette[data[j]*3];
	    destination[j*3 + 1] = palette[data[j]*3 + 1];
	    destination[j*3 + 2] = palette[data[j]*3 + 2];
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_textures[index].width, this->m_textures[index].height, 0, GL_RGB, GL_UNSIGNED_BYTE, destination);
	delete []data;
	delete []palette;
    }
    return id;
}

void MdlFile::cleanupTextureFromGl(GLuint id)
{
    if (this->m_file != 0)
    {
	glDeleteTextures(1, &id);
    }
}

void MdlFile::setupTextures()
{
    if (this->m_file != 0)
    {
        glGenTextures(this->m_header.textureCount, this->m_textureIndex);
        for (int i = 0; i < this->m_header.textureCount; i++)
        {
            glBindTexture(GL_TEXTURE_2D, this->m_textureIndex[i]);

            int dataSize = this->m_textures[i].width * this->m_textures[i].height;
            int paletteSize = 256 * 3;
            int paletteOffset = this->m_textures[i].index + (this->m_textures[i].width * this->m_textures[i].height);
            unsigned char* data = new unsigned char[dataSize];
            unsigned char* palette = new unsigned char[paletteSize];

            fseek(this->m_file, this->m_textures[i].index, SEEK_SET);
            fread(data, 1, dataSize, this->m_file);

            fseek(this->m_file, paletteOffset, SEEK_SET);
            fread(palette, 1, paletteSize, this->m_file);

            unsigned char* destination = new unsigned char[this->m_textures[i].width * this->m_textures[i].height * 3];
            for (int j = 0; j < dataSize; j++)
            {
                destination[j*3] = palette[data[j]*3];
                destination[j*3 + 1] = palette[data[j]*3 + 1];
                destination[j*3 + 2] = palette[data[j]*3 + 2];
            }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_textures[i].width, this->m_textures[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, destination);
            delete []data;
            delete []palette;
        }
    }
}

void MdlFile::cleanupTextures()
{
    if (this->m_file != 0)
    {
	glDeleteTextures(this->m_header.textureCount, this->m_textureIndex);
    }
}

