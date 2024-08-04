/* 
 * File:   containerview.cpp
 * Author: Wouter
 * 
 * Created on January 28, 2009, 4:11 PM
 */

#include "containerview.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "texturedialog.h"

using namespace std;

ContainerView::ContainerView()
        : GLControl("containerview"), m_textureContainer(0), m_selectedTexture(-1)
{
    this->m_style |=  WS_VSCROLL;
}

ContainerView::~ContainerView()
{
}

LRESULT ContainerView::objectProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            m_scrollInformation.fMask = SIF_POS | SIF_RANGE;
            m_scrollInformation.nPos = 0;
            m_scrollInformation.nMin = 0;
            m_scrollInformation.nMax = 1;
            SetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
            GetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation);

            EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_BOTH);
            break;
        }
        case WM_PAINT:
        {
	    this->useAsCurrent();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(0, this->m_width, 0, -this->m_height, -300.0f, 300.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            if (this->m_textureContainer != 0)
            {
                glScalef(1.0f, -1.0f, 1.0f);
                drawOverview();
            }
	    else
	    {
		cout << "No texture container to draw" << endl;
	    }

            SwapBuffers(this->m_hDC);
	    ValidateRect(this->m_hWnd, NULL);
            break;
        }
        case WM_VSCROLL:
        {
            GetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation);
            switch (LOWORD (wParam))
            {         // user clicked the HOME keyboard key
             case SB_TOP:
                  m_scrollInformation.nPos = m_scrollInformation.nMin;
                  break;

             // user clicked the END keyboard key
             case SB_BOTTOM:
                  m_scrollInformation.nPos = m_scrollInformation.nMax;
                  break;

             // user clicked the top arrow
             case SB_LINEUP:
                  m_scrollInformation.nPos -= 1;
                  break;

             // user clicked the bottom arrow
             case SB_LINEDOWN:
                  m_scrollInformation.nPos += 1;
                  break;

             // user clicked the scroll bar shaft above the scroll box
             case SB_PAGEUP:
                  m_scrollInformation.nPos -= m_scrollInformation.nPage;
                  break;

             // user clicked the scroll bar shaft below the scroll box
             case SB_PAGEDOWN:
                  m_scrollInformation.nPos += m_scrollInformation.nPage;
                  break;

             // user dragged the scroll box
             case SB_THUMBTRACK:
                  m_scrollInformation.nPos = m_scrollInformation.nTrackPos;
                  break;

             default:
                  break;

            }
            m_scrollInformation.fMask = SIF_POS;
            SetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
            GetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation);
            EnableScrollBar(this->m_hWnd, SB_VERT, ESB_ENABLE_BOTH);
            if (m_scrollInformation.nPos <= 0)
            {
                EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_UP);
                m_scrollInformation.nPos = 0;
            }
            if (m_scrollInformation.nPos >= m_scrollInformation.nMax)
            {
                EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_DOWN);
                m_scrollInformation.nPos = m_scrollInformation.nMax;
            }
            this->repaint();
            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
            {
                m_scrollInformation.nPos -= 1;
                if (m_scrollInformation.nPos < 0) m_scrollInformation.nPos = 0;
            }
            else
            {
                m_scrollInformation.nPos += 1;
                if (m_scrollInformation.nPos > m_scrollInformation.nMax) m_scrollInformation.nPos = m_scrollInformation.nMax;
            }
            SetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
            GetScrollInfo (this->m_hWnd, SB_VERT, &m_scrollInformation);
            EnableScrollBar(this->m_hWnd, SB_VERT, ESB_ENABLE_BOTH);
            if (m_scrollInformation.nPos <= 0)
            {
                EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_UP);
                m_scrollInformation.nPos = 0;
            }
            if (m_scrollInformation.nPos >= m_scrollInformation.nMax)
            {
                EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_DOWN);
                m_scrollInformation.nPos = m_scrollInformation.nMax;
            }
            this->repaint();
            break;
        }
        case WM_SIZE:
        {
            this->m_width = LOWORD(lParam);
            this->m_height = HIWORD(lParam);
            
            updateScrollbar();
            break;
        }
        case WM_LBUTTONDOWN:
        {
            if (this->m_textureContainer != 0)
            {
                SetFocus(this->m_hWnd);
                int x = LOWORD(lParam);
                int y = HIWORD(lParam);
                this->pickOverview(x, y);
                this->repaint();
            }
            break;
        }
        case WM_MBUTTONDOWN:
        {
            if (this->m_textureContainer != 0)
            {
                SetFocus(this->m_hWnd);
                int x = LOWORD(lParam);
                int y = HIWORD(lParam);
                this->pickOverview(x, y);
                this->repaint();
            }
            TextureDialog dlg;

            dlg.setTextureContainer(this->m_textureContainer);
            dlg.setCurrentTexture(this->m_selectedTexture);
            
            dlg.showModal(this->m_parent);
            break;
        }
        case WM_KEYDOWN:
        {
            int texturesPerRow = (this->m_width-20) / (TEXTUREPANEL_SIZE + 10);
            switch (wParam)
            {
                case VK_UP:
                {
                    this->selectTexture(this->m_selectedTexture - texturesPerRow);
                    break;
                }
                case VK_DOWN:
                {
                    this->selectTexture(this->m_selectedTexture + texturesPerRow);
                    break;
                }
                case VK_LEFT:
                {
                    this->selectTexture(this->m_selectedTexture - 1);
                    break;
                }
                case VK_RIGHT:
                {
                    this->selectTexture(this->m_selectedTexture + 1);
                    break;
                }
            }
            this->repaint();
            break;
        }
    }
    return GLControl::objectProc(msg, wParam, lParam);
}

void ContainerView::setTextureContainer(TextureContainer* tc)
{
    this->m_textureContainer = tc;
    this->updateScrollbar();
    this->repaint();
}

void ContainerView::selectTexture(int index)
{
    if (this->m_textureContainer != 0)
    {
        if (index < 0)
            index = 0;
        if (index > this->m_textureContainer->getTextureCount())
            index = this->m_textureContainer->getTextureCount() - 1;

        this->m_selectedTexture = index;

        int texturesPerRow = (this->m_width - TEXTUREVIEW_SPACING) / (TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING);
        int  row = (index) / texturesPerRow;
        int rowsPerPage = (this->m_height - TEXTUREVIEW_SPACING) / (TEXTUREPANEL_SIZE + TEXTUREPANEL_TEXTAREA + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING);
        if (rowsPerPage < 1) rowsPerPage = 1;

        if (m_scrollInformation.nPos > row)
            m_scrollInformation.nPos = row;
        if (m_scrollInformation.nPos < row - rowsPerPage + 1)
            m_scrollInformation.nPos = row - rowsPerPage + 1;

        if (m_scrollInformation.nPos > m_scrollInformation.nMax)
            m_scrollInformation.nPos = m_scrollInformation.nMax;

        SetScrollInfo (m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
    }
}

void ContainerView::updateScrollbar()
{
    if (this->m_textureContainer != 0)
    {
        int count = this->m_textureContainer->getTextureCount();
        int texturesPerRow = (this->m_width - TEXTUREVIEW_SPACING) / (TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING);
        if (texturesPerRow < 1) texturesPerRow = 1;

        int rowsPerPage = (this->m_height - TEXTUREVIEW_SPACING) / (TEXTUREPANEL_SIZE + TEXTUREPANEL_TEXTAREA + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING);
        if (rowsPerPage < 1) rowsPerPage = 1;

        int totalRows = count / texturesPerRow;
        int pages = count / (rowsPerPage*texturesPerRow);

        if(count % (rowsPerPage*texturesPerRow) > 0)
            pages += 1;
        if(count % texturesPerRow > 0)
            totalRows += 1;

        if (pages <= 1)
        {
            m_scrollInformation.fMask = SIF_RANGE | SIF_POS;
            m_scrollInformation.nMin = 0;
            m_scrollInformation.nMax = 1;
            if (m_scrollInformation.nPos > m_scrollInformation.nMax)
                m_scrollInformation.nPos = m_scrollInformation.nMax;

            SetScrollInfo (m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
            GetScrollInfo (m_hWnd, SB_VERT, &m_scrollInformation);
            EnableScrollBar(this->m_hWnd, SB_VERT, ESB_DISABLE_BOTH);
        }
        else
        {
            m_scrollInformation.fMask = SIF_RANGE | SIF_POS;
            m_scrollInformation.nMin = 0;
            m_scrollInformation.nMax = totalRows - rowsPerPage;
            if (m_scrollInformation.nPos > m_scrollInformation.nMax)
                m_scrollInformation.nPos = m_scrollInformation.nMax;

            SetScrollInfo (m_hWnd, SB_VERT, &m_scrollInformation, TRUE);
            GetScrollInfo (m_hWnd, SB_VERT, &m_scrollInformation);
            EnableScrollBar(this->m_hWnd, SB_VERT, ESB_ENABLE_BOTH);
        }
    }
}

void ContainerView::drawTexture(float x, float y, int w, int h, GLuint textureID, String name, bool selected)
{
    float panel_width = TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER;
    float panel_height = TEXTUREPANEL_SIZE + TEXTUREPANEL_TEXTAREA + TEXTUREPANEL_BORDER;
    float tx = x + TEXTUREPANEL_BORDER;
    float ty = y + TEXTUREPANEL_BORDER + TEXTUREPANEL_TEXTAREA;
    float tw = tx + panel_width - (2 * TEXTUREPANEL_BORDER);
    float th = ty + panel_height - (2 * TEXTUREPANEL_BORDER) - TEXTUREPANEL_TEXTAREA;

    glDisable(GL_TEXTURE_2D);

    glRasterPos2f(x, y);
    if (selected)
    {
        if (this->m_focused)
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else
        {
            glColor3f(0.7f, 0.7f, 0.7f);
        }
        drawRoundedRectangle(GL_LINE_LOOP, x, y, x + panel_width, y + panel_height);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    drawRoundedRectangle(GL_POLYGON, x, y, x + panel_width, y + panel_height);

    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawRoundedRectangle(GL_LINE_LOOP, x, y, x + panel_width, y + panel_height);

    glColor3f(0.0f, 0.0f, 0.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(tx, ty - TEXTUREPANEL_TEXTAREA);
    glListBase(this->m_font);
    glCallLists(name.Length(), GL_BYTE, (const char*)name);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(tx, th);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(tw, th);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(tw, ty);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(tx, ty);
    glEnd();
}

void ContainerView::drawOverview(bool picking)
{
    int texturesPerRow = this->m_width / (TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER);
    int x = TEXTUREVIEW_SPACING;
    int y = this->m_height - TEXTUREPANEL_SIZE - TEXTUREPANEL_TEXTAREA - TEXTUREPANEL_BORDER - TEXTUREVIEW_SPACING;
    int start = (m_scrollInformation.nPos) * texturesPerRow;

    for (int i = start; i < this->m_textureContainer->getTextureCount(); i++)
    {
        if (picking) glLoadName(i);
        int w, h, textureID = this->m_textureContainer->getTextureID(i);
        String name = this->m_textureContainer->getTextureName(i);
        this->m_textureContainer->getTextureSize(i, w, h);
        this->drawTexture(x, y, w, h, textureID, name, (i == this->m_selectedTexture));

        x += TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING;
        if (x > (this->m_width - TEXTUREPANEL_SIZE + TEXTUREPANEL_BORDER - TEXTUREVIEW_SPACING))
        {
            x = TEXTUREVIEW_SPACING;
            y -= TEXTUREPANEL_SIZE + TEXTUREPANEL_TEXTAREA + TEXTUREPANEL_BORDER + TEXTUREVIEW_SPACING;
        }
    }
}

void ContainerView::pickOverview(int mouse_x, int mouse_y)
{
    GLuint buffer[512];
    GLint hits;

    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(512, buffer);

    (void) glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]-mouse_y), 1.0f, 1.0f, viewport);

    glOrtho(0, this->m_width, 0, -this->m_height, -300.0f, 300.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1.0f, -1.0f, 1.0f);

    drawOverview(true);

    hits = glRenderMode(GL_RENDER);

    if (hits > 0)
    {
        this->m_selectedTexture = buffer[3];
        int depth = buffer[1];

        for (int loop = 1; loop < hits; loop++)
        {
            if (buffer[loop*4+1] < GLuint(depth))
            {
                this->m_selectedTexture = buffer[loop*4+3];
                depth = buffer[loop*4+1];
            }
        }
    }
}
