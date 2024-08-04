/* 
 * File:   miptexbasedfile.cpp
 * Author: Administrator
 * 
 * Created on March 13, 2009, 11:53 AM
 */

#include "miptexbasedfile.h"

MiptexBasedFile::MiptexBasedFile()
{
}

MiptexBasedFile::~MiptexBasedFile()
{
}

void MiptexBasedFile::createTextureFromMiptex(unsigned char* data, bool blueIsInvisible)
{
    tBSPMipTexHeader* miptex = (tBSPMipTexHeader*)data;
    int s = miptex->width * miptex->height;
    int paletteOffset = miptex->offsets[0] + s + (s/4) + (s/16) + (s/64) + 2;

    unsigned char* source = data + miptex->offsets[0];
    unsigned char* palette = data + paletteOffset;
    unsigned char* destination = new unsigned char[s * 4];

    int j = 0;
    for (int i = 0; i < s; i++)
    {
        destination[j++] = palette[source[i]*3];
        destination[j++] = palette[source[i]*3+1];
        destination[j++] = palette[source[i]*3+2];
        destination[j++] = 255;
        if (blueIsInvisible)
        {
            if (palette[source[i]*3] <= 5 && palette[source[i]*3+1] <= 5 &&palette[source[i]*3+2] < 250)
		destination[j-1] = 0;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, miptex->width, miptex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, destination);
}

