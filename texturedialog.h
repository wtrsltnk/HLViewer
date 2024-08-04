/* 
 * File:   texturedialog.h
 * Author: Administrator
 *
 * Created on February 25, 2009, 6:49 AM
 */

#ifndef _TEXTUREDIALOG_H
#define	_TEXTUREDIALOG_H

#include "dialog.h"
#include "texturecontainer.h"
#include "button.h"
#include "textureview.h"

#define ID_NEXTTEXTURE_BUTTON 1
#define ID_PREVTEXTURE_BUTTON 2

class TextureDialog : public ui::Dialog
{
public:
    TextureDialog();
    virtual ~TextureDialog();

    void setTextureContainer(TextureContainer* container);
    void setCurrentTexture(int current);

protected:
    virtual LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void onInitializeDialog();

private:
    TextureContainer* m_container;
    int m_currentTexture;

    ui::Button m_nextTexture;
    ui::Button m_prevTexture;
    TextureView m_view;

    void stepTexture(int step);
};

#endif	/* _TEXTUREDIALOG_H */

