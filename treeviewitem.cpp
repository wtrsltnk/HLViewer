#include "treeview.h"

using namespace ui;

TreeViewItem::TreeViewItem(const TreeView* parent, HTREEITEM item)
	: m_parent(parent), m_item(item)
{
}

TreeViewItem::TreeViewItem(const TreeViewItem& item)
	: m_parent(item.m_parent), m_item(item.m_item)
{
}

TreeViewItem::~TreeViewItem()
{
}

String TreeViewItem::getText() const
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_TEXT;
    item.hItem = m_item;

    TreeView_GetItem(m_parent->getHandle(), &item);

    return item.pszText;
}

void TreeViewItem::setText(String text)
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_TEXT;
    item.hItem = m_item;
    item.pszText = text;
    item.cchTextMax = text.Length();

    TreeView_SetItem(m_parent->getHandle(), &item);
}

void* TreeViewItem::getData() const
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_PARAM;
    item.hItem = m_item;

    TreeView_GetItem(m_parent->getHandle(), &item);

    return (void*)item.lParam;
}

void TreeViewItem::setData(void* data)
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_PARAM;
    item.hItem = m_item;
    item.lParam = (LPARAM)data;

    TreeView_SetItem(m_parent->getHandle(), &item);
}

bool TreeViewItem::getCheckState() const
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_STATE;
    item.hItem = m_item;
    item.stateMask = TVIS_STATEIMAGEMASK;

    TreeView_GetItem(m_parent->getHandle(), &item);

    return ((item.state >> 12) -1) == 0;
}

void TreeViewItem::setCheckState(bool state)
{
    TVITEM item = { 0 };

    item.mask = TVIF_HANDLE | TVIF_STATE;
    item.hItem = m_item;
    item.stateMask = TVIS_STATEIMAGEMASK;
    /*
    Since state images are one-based, 1 in this macro turns the check off, and
    2 turns it on.
    */
    item.state = INDEXTOSTATEIMAGEMASK((state ? 2 : 1));

    TreeView_SetItem(m_parent->getHandle(), &item);
}

TreeViewItem TreeViewItem::addItem(String text, int image, int selimage, DWORD data, int state)
{
    TV_INSERTSTRUCT tvins;
    TV_ITEM tvi;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
    tvi.pszText = (LPSTR)(const char*)text;
    tvi.iImage = image;
    tvi.iSelectedImage = selimage;
    tvi.lParam = data;
    tvi.state = state;

    tvins.hParent = this->m_item;
    tvins.hInsertAfter = TVI_LAST;
    tvins.item = tvi;

    return TreeViewItem(this->m_parent, TreeView_InsertItem(this->m_parent->getHandle(), &tvins));
}

void TreeViewItem::removeMe()
{
    TreeView_DeleteItem(m_parent->getHandle(), this->m_item);
}

TreeViewItem TreeViewItem::getParent() const
{
    return TreeViewItem(m_parent, TreeView_GetParent(this->m_parent->getHandle(), this->m_item));
}

TreeViewItem TreeViewItem::getFirstChild() const
{
    return TreeViewItem(m_parent, TreeView_GetChild(this->m_parent->getHandle(), this->m_item));
}

TreeViewItem TreeViewItem::getNextSibling() const
{
    return TreeViewItem(m_parent, TreeView_GetNextSibling(this->m_parent->getHandle(), this->m_item));
}

void TreeViewItem::clearChilds()
{
    HTREEITEM child = TreeView_GetChild(this->m_parent->getHandle(), this->m_item);

    while (child)
    {
        TreeView_DeleteItem(this->m_parent->getHandle(), child);

        child = TreeView_GetChild(this->m_parent->getHandle(), this->m_item);
    }
}

bool TreeViewItem::hasChilds()
{
    return TreeView_GetChild(this->m_parent->getHandle(), this->m_item) != NULL;
}

void TreeViewItem::expand()
{
    TreeView_Expand(this->m_parent->getHandle(), this->m_item, TVE_EXPAND);
}

void TreeViewItem::collapse()
{
    TreeView_Expand(this->m_parent->getHandle(), this->m_item, TVE_COLLAPSE);
}

bool TreeViewItem::isValid()
{
    return this->m_item != NULL;
}
