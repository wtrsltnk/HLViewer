/*
 * File:   TreeView.cpp
 * Author: Wouter
 *
 * Created on February 25, 2009, 7:58 AM
 */

#include "treeview.h"

using namespace ui;

TreeView::TreeView()
        : Control("SysTreeView32")
{
    this->m_exStyle = WS_EX_CLIENTEDGE;
    this->m_style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_SHOWSELALWAYS;
    InitCommonControls();
}

TreeView::TreeView(DWORD id)
        : Control("SysTreeView32", id)
{
    this->m_exStyle = WS_EX_CLIENTEDGE;
    this->m_style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_SHOWSELALWAYS;
    InitCommonControls();
}

TreeView::~TreeView()
{
}

TreeViewItem TreeView::getFirstItem() const
{
    return TreeViewItem(this, TreeView_GetRoot(this->m_hWnd));
}

TreeViewItem TreeView::addItem(String text, int image, int selimage, DWORD data, int state)
{
    TV_INSERTSTRUCT tvins;
    TV_ITEM tvi;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
    tvi.pszText = (LPSTR)(const char*)text;
    tvi.iImage = image;
    tvi.iSelectedImage = selimage;
    tvi.lParam = data;
    tvi.state = state;

    tvins.hParent = TVI_ROOT;
    tvins.hInsertAfter = TVI_LAST;
    tvins.item = tvi;

    return TreeViewItem(this, TreeView_InsertItem(this->m_hWnd, &tvins));
}

void TreeView::clearItems()
{
    TreeView_DeleteAllItems(this->m_hWnd);
}

TreeViewItem TreeView::getSelectedItem() const
{
    return TreeViewItem(this, TreeView_GetSelection(this->m_hWnd));
}

HIMAGELIST TreeView::setNormalImageList(HIMAGELIST himl)
{
    return TreeView_SetImageList(this->m_hWnd, himl, LVSIL_NORMAL);
}

TreeViewItem TreeView::hitTestCursor()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(this->m_hWnd, &pt);
    
    TVHITTESTINFO htinfo;
    htinfo.pt.x = pt.x;
    htinfo.pt.y = pt.y;
    htinfo.flags = TVHT_ONITEM;

    TreeView_HitTest(this->m_hWnd, &htinfo);

    return TreeViewItem(this, htinfo.hItem);
}
