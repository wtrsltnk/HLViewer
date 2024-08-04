#include "listview.h"

using namespace ui;

ListViewItem::ListViewItem(const ListView* parent, LVITEM item)
	: m_parent(parent), m_item(item)
{
}

ListViewItem::~ListViewItem()
{
}

String ListViewItem::getText() const
{
    return (String)this->m_item.pszText;
}

void ListViewItem::setText(String text)
{
    ListView_SetItemText(this->m_parent->getHandle(), this->m_item.iItem, this->m_item.iSubItem, (char*)text);
}

ListViewItem ListViewItem::getSubItem(int index) const
{
    LVITEM lvi = { 0 };

    lvi.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVIF_PARAM;
    lvi.iItem = m_item.iItem;
    lvi.iSubItem = index;

    ListView_GetItem(this->m_parent->getHandle(), &lvi);
    
    return ListViewItem(m_parent, lvi);
}

void ListViewItem::setSubItemtext(String text, int index)
{
    ListViewItem subItem = getSubItem(index);
    subItem.setText(text);
}

void* ListViewItem::getData() const
{
    return (void*)this->m_item.lParam;
}
