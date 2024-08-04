/*
 * File:   textureview.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 3:19 PM
 */

#ifndef _TEXTUREVIEW_H
#define _TEXTUREVIEW_H

#include "glcontrol.h"

class TextureView : public ui::GLControl
{
public:
    TextureView();
    virtual ~TextureView();

    void setTexture(GLuint id, int width, int height);
    GLuint getTextureID() const;

    void zoom(float zoom);

private:
    LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);
    void drawTexture();

    GLuint m_textureID;
    int m_textureWidth;
    int m_textureHeight;
    float m_zoomFactor;
};

#endif /* _TEXTUREVIEW_H */
