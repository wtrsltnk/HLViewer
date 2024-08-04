/* 
 * File:   textureview.cpp
 * Author: Administrator
 * 
 * Created on February 25, 2009, 3:19 PM
 */

#include "textureview.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

TextureView::TextureView()
	: ui::GLControl("textureview"), m_textureID(0), m_zoomFactor(1.0f)
{
    this->m_exStyle = WS_EX_STATICEDGE;
}

TextureView::~TextureView()
{
}

void TextureView::setTexture(GLuint id, int width, int height)
{
    this->m_textureID = id;
    this->m_textureWidth = width;
    this->m_textureHeight = height;
}

GLuint TextureView::getTextureID() const
{
    return this->m_textureID;
}

void TextureView::zoom(float zoom)
{
    this->m_zoomFactor += zoom;
}

LRESULT TextureView::objectProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
	case WM_CREATE:
	{
	    break;
	}
	case WM_PAINT:
	{
	    this->useAsCurrent();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

	    glOrtho(-(this->m_width/2), (this->m_width/2), (this->m_height/2), -(this->m_height/2), -3.0f, 3.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

	    glScalef(1.0f, -1.0f, 1.0f);

	    drawTexture();
	    
            SwapBuffers(this->m_hDC);
	    ValidateRect(this->m_hWnd, NULL);
	    break;
	}
	case WM_SIZE:
	{
	    this->m_width = LOWORD(lParam);
	    this->m_height = HIWORD(lParam);
	    repaint();
	    break;
	}
    }
    ui::GLControl::objectProc(msg, wParam, lParam);
}

void TextureView::drawTexture()
{
    int w = this->m_textureWidth, h = this->m_textureHeight;

    w = int(w * this->m_zoomFactor);
    h = int(h * this->m_zoomFactor);
    
    glBindTexture(GL_TEXTURE_2D, this->m_textureID);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-w, -h); glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-w,  h); glTexCoord2f(1.0f, 0.0f);
    glVertex2f( w,  h); glTexCoord2f(1.0f, 1.0f);
    glVertex2f( w, -h); glTexCoord2f(0.0f, 1.0f);
    glEnd();
}
