/* 
 * File:   containerview.h
 * Author: Wouter
 *
 * Created on January 28, 2009, 4:11 PM
 */

#ifndef _CONTAINERVIEW_H
#define	_CONTAINERVIEW_H

#define TEXTUREPANEL_SIZE 150
#define TEXTUREPANEL_BORDER 8
#define TEXTUREPANEL_TEXTAREA 12
#define TEXTUREVIEW_SPACING 5

#include "glcontrol.h"

class ContainerView : public ui::GLControl
{
public:
    ContainerView();
    virtual ~ContainerView();

    void setTextureContainer(TextureContainer* tc);
    void selectTexture(int index);

protected:
    TextureContainer* m_textureContainer;
    int m_selectedTexture;
    SCROLLINFO m_scrollInformation;

    LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);

    void drawTexture(float x, float y, int w, int h, GLuint textureID, String name, bool selected);
    void drawOverview(bool picking = false);
    void pickOverview(int x, int y);
    void updateScrollbar();
};

#endif	/* _CONTAINERVIEW_H */

