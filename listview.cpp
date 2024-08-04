/* 
 * File:   listview.cpp
 * Author: Wouter
 * 
 * Created on January 26, 2009, 1:01 AM
 */

#include "listview.h"

using namespace ui;

ListView::ListView()
        : Control("SysListView32")
{
    this->m_style |= LVS_SHOWSELALWAYS;
    ::InitCommonControls();
}

ListView::ListView(DWORD id)
        : Control("SysListView32", id)
{
    this->m_style |= LVS_SHOWSELALWAYS;
    ::InitCommonControls();
}

ListView::~ListView()
{
}

void ListView::createHeader()
{
    this->m_header = CreateWindow(  WC_HEADER,
                                    "",
                                    HDS_HORZ|HDS_BUTTONS,
                                    this->m_x,
                                    this->m_y,
                                    this->m_width + 10,
                                    this->m_height,
                                    this->m_hWnd,
                                    NULL,
                                    GetModuleHandle(NULL),
                                    NULL );
}

ListViewItem ListView::getItem(int index) const
{
    LVITEM lvi = { 0 };

    lvi.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVIF_PARAM;
    lvi.iItem = index;
    lvi.iSubItem = 0;

    ListView_GetItem(this->m_hWnd, &lvi);
    
    return ListViewItem(this, lvi);
}

void ListView::addColumn(String title, int width, int index)
{
    LV_COLUMN lvc;

    lvc.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
    lvc.fmt = LVCFMT_LEFT ;
    lvc.cchTextMax = 300;
    lvc.cx = width;
    lvc.pszText = title;
    lvc.iSubItem = index;

    ListView_InsertColumn(this->m_hWnd, index, &lvc);
}

void ListView::removeColumn(int index)
{
    ListView_DeleteColumn(this->m_hWnd, index);
}

void ListView::clearColumns()
{
    int result = 1;

    while (result)
    {
        result = ListView_DeleteColumn(this->m_hWnd, 0);
    }
}

ListViewItem ListView::addItem(String text, int index, int image, LPARAM data)
{
    LV_ITEM lvi;

    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
    lvi.state = 0;
    lvi.stateMask = 0;
    lvi.iItem = index;
    lvi.iSubItem = 0;
    lvi.pszText = (LPSTR)(const char*)text;
    lvi.iImage = image;
    lvi.lParam = data;

    ListView_InsertItem(this->m_hWnd, &lvi);
    return ListViewItem(this, lvi);
}

void ListView::removeItem(int index)
{
    ListView_DeleteItem(this->m_hWnd, index);
}

void ListView::clearItems()
{
    ListView_DeleteAllItems(this->m_hWnd);
}

HIMAGELIST ListView::setNormalImageList(HIMAGELIST himl)
{
    return ListView_SetImageList(this->m_hWnd, himl, LVSIL_NORMAL);
}

HIMAGELIST ListView::setSmallImageList(HIMAGELIST himl)
{
    return ListView_SetImageList(this->m_hWnd, himl, LVSIL_SMALL);
}
