/* 
 * File:   glcontrol.cpp
 * Author: Wouter
 * 
 * Created on January 24, 2009, 2:47 PM
 */

#include "glcontrol.h"
#include "window.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

using namespace ui;

GLControl::GLControl(LPTSTR className)
        : Window(className), m_hDC(0), m_hRC(0), m_focused(false)
{
    this->m_style = WS_CHILD;
    this->m_exStyle = WS_EX_CLIENTEDGE;
}

GLControl::~GLControl()
{
}

LRESULT GLControl::objectProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            GLuint uiPixelFormat = 0;

            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
                1,				// Version Number
                PFD_DRAW_TO_WINDOW |		// Format Must Support Window
                PFD_SUPPORT_OPENGL |		// Format Must Support OpenGL
                PFD_DOUBLEBUFFER,		// Must Support Double Buffering
                PFD_TYPE_RGBA,			// Request An RGBA Format
                24,				// Select Our Color Depth
                0, 0, 0, 0, 0, 0,		// Color Bits Ignored
                0,				// No Alpha Buffer
                0,				// Shift Bit Ignored
                0,				// No Accumulation Buffer
                0, 0, 0, 0,			// Accumulation Bits Ignored
                16,				// 16Bit Z-Buffer (Depth Buffer)
                0,				// No Stencil Buffer
                0,				// No Auxiliary Buffer
                PFD_MAIN_PLANE,			// Main Drawing Layer
                0,				// Reserved
                0, 0, 0				// Layer Masks Ignored
            };

            if (this->m_hWnd != NULL)
            {
                if (!(this->m_hDC = ::GetDC(this->m_hWnd)))
                {
                    printf("Error creating Device Context");
                    this->destroyGLControl();
                    break;
                }

                if (!(uiPixelFormat = ::ChoosePixelFormat(this->m_hDC, &pfd)))
                {
                    printf("Error choosing Pixel Format");
                    this->destroyGLControl();
                    break;
                }

                if (!::SetPixelFormat(this->m_hDC, uiPixelFormat, &pfd))
                {
                    printf("Error setting Pixel Format");
                    this->destroyGLControl();
                    break;
                }

                if (!(this->m_hRC = ::wglCreateContext(this->m_hDC)))
                {
                    printf("Error creating Render Context");
                    this->destroyGLControl();
                    break;
                }

                if (!::wglMakeCurrent(this->m_hDC, this->m_hRC))
                {
                    printf("Error making current Context");
                    this->destroyGLControl();
                    break;
                }
                
                this->createGLFont();

                glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
                glClearDepth(1.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glShadeModel(GL_FLAT);
                
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_BLEND);
                glEnable(GL_TEXTURE_2D);
            }
            break;
        }
        case WM_SIZE:
        {
	    this->useAsCurrent();
            this->m_width = LOWORD(lParam);
            this->m_height = HIWORD(lParam);
            
            glViewport(0, 0, this->m_width, this->m_height);
            break;
        }
        case WM_DESTROY:
        {
            this->destroyGLControl();
            break;
        }
        case WM_SETFOCUS:
        {
            this->m_focused = true;
            break;
        }
        case WM_KILLFOCUS:
        {
            this->m_focused = false;
            this->repaint();
            break;
        }
    }
    return DefWindowProc(this->m_hWnd, msg, wParam, lParam);
}

bool GLControl::createGLControl(Window* parent)
{
    this->m_parent = parent;
    return this->show(parent);
}

void GLControl::useAsCurrent() const
{
    wglMakeCurrent(this->m_hDC, this->m_hRC);
}

void GLControl::move(int x, int y)
{
    this->m_x = x;
    this->m_y = y;

    ::MoveWindow(this->m_hWnd, this->m_x, this->m_y, this->m_width, this->m_height, TRUE);
}

void GLControl::resize(int width, int height)
{
    this->m_width = width;
    this->m_height = height;

    ::MoveWindow(this->m_hWnd, this->m_x, this->m_y, this->m_width, this->m_height, TRUE);
}

void GLControl::repaint() const
{
    this->useAsCurrent();
    InvalidateRect(this->m_hWnd, NULL, FALSE);
}

void GLControl::createGLFont()
{
    this->useAsCurrent();
    this->m_font = glGenLists(255);

    HFONT verdana = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE,
                    FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS,
                    CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                    FF_DONTCARE | DEFAULT_PITCH, "Courier New" );

    HGDIOBJ tmp = SelectObject(this->m_hDC, verdana);

    wglUseFontBitmaps(this->m_hDC, 0, 255, this->m_font);

    SelectObject(this->m_hDC, tmp);
    DeleteObject(verdana);
}

void GLControl::drawRectangle(GLenum mode, float minx, float miny, float maxx, float maxy)
{
    glBegin(mode);

    glVertex2f(maxx, miny);
    glVertex2f(maxx, maxy);
    glVertex2f(minx, maxy);
    glVertex2f(minx, miny);

    glEnd();
}

void GLControl::drawRoundedRectangle(GLenum mode, float minx, float miny, float maxx, float maxy)
{
    float rad = 10.0f;
    int roundboxtype = 15;
    float vec[7][2]= {{0.195, 0.02}, {0.383, 0.067}, {0.55, 0.169}, {0.707, 0.293},
                  {0.831, 0.45}, {0.924, 0.617}, {0.98, 0.805}};
    int a;

    /* mult */
    for(a=0; a<7; a++) {
        vec[a][0]*= rad; vec[a][1]*= rad;
    }

    glBegin(mode);

    /* start with corner right-bottom */
    if(roundboxtype & 4) {
        glVertex2f( maxx-rad, miny);
        for(a=0; a<7; a++) {
            glVertex2f( maxx-rad+vec[a][0], miny+vec[a][1]);
        }
        glVertex2f( maxx, miny+rad);
    }
    else glVertex2f( maxx, miny);

    /* corner right-top */
    if(roundboxtype & 2) {
        glVertex2f( maxx, maxy-rad);
        for(a=0; a<7; a++) {
            glVertex2f( maxx-vec[a][1], maxy-rad+vec[a][0]);
        }
        glVertex2f( maxx-rad, maxy);
    }
    else glVertex2f( maxx, maxy);

    /* corner left-top */
    if(roundboxtype & 1) {
        glVertex2f( minx+rad, maxy);
        for(a=0; a<7; a++) {
            glVertex2f( minx+rad-vec[a][0], maxy-vec[a][1]);
        }
        glVertex2f( minx, maxy-rad);
    }
    else glVertex2f( minx, maxy);

    /* corner left-bottom */
    if(roundboxtype & 8) {
        glVertex2f( minx, miny+rad);
        for(a=0; a<7; a++) {
            glVertex2f( minx+vec[a][1], miny+rad-vec[a][0]);
        }
        glVertex2f( minx+rad, miny);
    }
    else glVertex2f( minx, miny);

    glEnd();
}

void GLControl::destroyGLControl()
{
    if (this->m_hRC != NULL)
    {
        if (!::wglMakeCurrent(NULL, NULL))
        {
            printf("Error finalizing current Context %d\n", GetLastError());
        }

        if (!::wglDeleteContext(this->m_hRC))
        {
            printf("Error deleting Render Context\n");
        }
        this->m_hRC = NULL;
    }

    if (this->m_hDC != NULL)
    {
        if (::ReleaseDC(this->m_hWnd, this->m_hDC) == 0)
        {
            printf("Error releasing Device Context\n");
        }
        this->m_hDC = NULL;
    }
}

