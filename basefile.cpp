/* 
 * File:   basefile.cpp
 * Author: Administrator
 * 
 * Created on March 13, 2009, 6:01 PM
 */

#include "basefile.h"

BaseFile::BaseFile()
	: m_file(0)
{
}

BaseFile::~BaseFile()
{
    closeFile();
}

bool BaseFile::openFile(String filename)
{
    if (this->m_file = fopen(filename, "rb"))
    {
        this->m_filename = filename;
	return this->postOpenFile();
    }
    return false;
}

void BaseFile::closeFile()
{
    this->preCloseFile();
    
    if (this->m_file != false)
        fclose(this->m_file);
    this->m_file = 0;
}

bool BaseFile::readData(char* data, int size, int offset)
{
    if (offset > -1)
        fseek(this->m_file, offset, SEEK_SET);
    
    return (fread(data, 1, size, this->m_file) == size);
}
