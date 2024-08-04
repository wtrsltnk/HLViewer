/* 
 * File:   glcontrol.h
 * Author: Wouter
 *
 * Created on January 24, 2009, 2:47 PM
 */

#ifndef _GLCONTROL_IMP_H
#define	_GLCONTROL_IMP_H

#include "window.h"
#include "texturecontainer.h"

namespace ui
{
    class GLControl : protected Window
    {
    public:
	GLControl(LPTSTR className = "OpenGL");
	virtual ~GLControl();

	bool createGLControl(Window* parent = NULL);
	void useAsCurrent() const;
	void move(int x, int y);
	void resize(int width, int height);
	void repaint() const;
	void destroyGLControl();

    protected:
	HDC m_hDC;
	HGLRC m_hRC;
	int m_x, m_y, m_width, m_height;
	int m_font;
	bool m_focused;
	Window* m_parent;

	LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void createGLFont();
    	static void drawRoundedRectangle(GLenum mode, float x, float y, float w, float h);
        static void drawRectangle(GLenum mode, float minx, float miny, float maxx, float maxy);
    };
}

#endif	/* _GLCONTROL_IMP_H */

