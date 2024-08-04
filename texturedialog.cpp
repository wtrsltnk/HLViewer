/* 
 * File:   texturedialog.cpp
 * Author: Administrator
 * 
 * Created on February 25, 2009, 6:49 AM
 */

#include "texturedialog.h"
#include <stdio.h>
#include <iostream>

using namespace std;

TextureDialog::TextureDialog()
        : Dialog("texturedialog"), m_container(NULL), m_currentTexture(0)
{
    this->m_strWindowTitle = "Texture";
    this->m_width = 400;
    this->m_height = 400;
    this->m_exStyle = WS_EX_DLGMODALFRAME;
}

TextureDialog::~TextureDialog()
{
}

void TextureDialog::setTextureContainer(TextureContainer* container)
{
    this->m_container = container;
}

void TextureDialog::setCurrentTexture(int current)
{
    this->m_currentTexture = current;
}

LRESULT TextureDialog::objectProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
	case WM_CREATE:
	{
	    this->m_prevTexture.setID(ID_PREVTEXTURE_BUTTON);
	    this->m_prevTexture.createControl(this);
	    this->m_prevTexture.setText("Prev");
	    this->m_prevTexture.resize(100, 30);

	    this->m_nextTexture.setID(ID_NEXTTEXTURE_BUTTON);
	    this->m_nextTexture.createControl(this);
	    this->m_nextTexture.setText("Next");
	    this->m_nextTexture.resize(100, 30);

	    this->m_view.createGLControl(this);

	    break;
	}
	case WM_SIZE:
	{
	    int width = LOWORD(lParam);
	    int height = HIWORD(lParam);
	    this->m_nextTexture.move(width - 100, 0);
	    this->m_view.move(0, 30);
	    this->m_view.resize(width, height-30);
	    break;
	}
	case WM_COMMAND:
	{
	    switch (wParam)
	    {
		case ID_NEXTTEXTURE_BUTTON:
		{
		    this->stepTexture(1);
		    break;
		}
		case ID_PREVTEXTURE_BUTTON:
		{
		    this->stepTexture(-1);
		    break;
		}
	    }
	}
	case WM_MOUSEWHEEL:
	{
	    int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	    this->m_view.zoom(float(zDelta) / 1200.0f);
	    this->m_view.repaint();
	    break;
	}
    }
    return Dialog::objectProc(msg, wParam, lParam);
}

void TextureDialog::onInitializeDialog()
{
    GLuint newID = this->m_container->setupTextureToGl(this->m_currentTexture);
    int newWidth, newHeight;
    this->m_container->getTextureSize(this->m_currentTexture, newWidth, newHeight);
    this->m_view.setTexture(newID, newWidth, newHeight);

    this->setText(this->m_container->getTextureName(this->m_currentTexture));
    this->m_view.repaint();
}

void TextureDialog::stepTexture(int step)
{
    GLuint currentID = this->m_view.getTextureID();
    if (this->m_container != NULL)
    {
	this->m_view.useAsCurrent();
	this->m_container->cleanupTextureFromGl(currentID);

	this->m_currentTexture += step;

	if (this->m_currentTexture > this->m_container->getTextureCount()-1)
	    this->m_currentTexture = 0;
	else if (this->m_currentTexture < 0)
	    this->m_currentTexture = this->m_container->getTextureCount() - 1;

	GLuint newID = this->m_container->setupTextureToGl(this->m_currentTexture);
	int newWidth, newHeight;
	this->m_container->getTextureSize(this->m_currentTexture, newWidth, newHeight);
	this->m_view.setTexture(newID, newWidth, newHeight);
	this->m_view.repaint();

	this->setText(this->m_container->getTextureName(this->m_currentTexture));
    }
}
