/*
 * File:   TreeView.h
 * Author: Wouter
 *
 * Created on June 27, 2008, 12:27 AM
 */

#ifndef _TREEVIEW_IMP_H
#define _TREEVIEW_IMP_H

#include "Common/string.h"
#include "control.h"
#include <commctrl.h>

namespace ui
{
    class TreeViewItem;

    class TreeView : public Control
    {
    public:
        TreeView();
        TreeView(DWORD id);
        virtual ~TreeView();

        TreeViewItem getFirstItem() const;
        TreeViewItem addItem(String text, int image, int selimage, DWORD data, int state = 0);

        TreeViewItem getSelectedItem() const;

        void clearItems();

        HIMAGELIST setNormalImageList(HIMAGELIST himl);

        TreeViewItem hitTestCursor();
    };

    class TreeViewItem
    {
    public:
        TreeViewItem(const TreeView *parent, HTREEITEM item);
        TreeViewItem(const TreeViewItem &item);
        virtual ~TreeViewItem();

        String getText() const;
        void setText(String text);

        void *getData() const;
        void setData(void *data);

        bool getCheckState() const;
        void setCheckState(bool state);

        TreeViewItem addItem(String text, int image, int selimage, DWORD data, int state = 0);
        void removeMe();

        TreeViewItem getParent() const;
        TreeViewItem getFirstChild() const;
        TreeViewItem getNextSibling() const;

        void clearChilds();
        bool hasChilds();

        void expand();
        void collapse();

        bool isValid();

    private:
        const TreeView *m_parent = nullptr;
        HTREEITEM m_item = nullptr;
    };
} // namespace ui

#endif /* _TREEVIEW_IMP_H */
