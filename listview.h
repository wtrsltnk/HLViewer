/* 
 * File:   listview.h
 * Author: Wouter
 *
 * Created on January 26, 2009, 1:01 AM
 */

#ifndef _LISTVIEW_IMP_H
#define	_LISTVIEW_IMP_H

#include "control.h"
#include <commctrl.h>
#include "Common/string.h"

namespace ui
{
    class ListViewItem;
    
    class ListView : public Control
    {
    public:
	ListView();
	ListView(DWORD id);
	~ListView();

	void createHeader();

	ListViewItem getItem(int index) const;

	void addColumn(String title, int width, int index);
	void removeColumn(int index);
	void clearColumns();

	ListViewItem addItem(String text, int index, int image = 0, LPARAM data = NULL);
	void removeItem(int index);
	void clearItems();

	HIMAGELIST setNormalImageList(HIMAGELIST himl);
	HIMAGELIST setSmallImageList(HIMAGELIST himl);

    private:
	HWND m_header;
    };
    
    class ListViewItem
    {
    public:
	ListViewItem(const ListView* parent, LVITEM item);
	virtual ~ListViewItem();

	String getText() const;
	void setText(String text);

	ListViewItem getSubItem(int index) const;
	void setSubItemtext(String text, int index);

	void* getData() const;

    private:
	LVITEM m_item;
	const ListView* m_parent;

    };
}

#endif	/* _LISTVIEW_IMP_H */

