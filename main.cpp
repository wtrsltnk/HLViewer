#include "main.h"
#include "dialog.h"
#include "error.h"
#include "main.h"
#include "mdlfile.h"
#include <commdlg.h>
#include <stdio.h>

using namespace std;

Main::Main(int argc, char *argv[])
    : Window("MainWindow"), m_currentContainer(0)
{
    this->m_strWindowTitle = "HLViewer";
    this->m_exStyle = WS_EX_WINDOWEDGE;

    this->m_hMenu = this->buildMenu();
    this->parseArgs(argc, argv);
}

Main::~Main()
{
}

void Main::parseArgs(int argc, char *argv[])
{
    if (argc >= 1)
    {
        this->m_fileFromArguments = argv[1];
    }
}

LRESULT Main::objectProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            this->m_tv.createControl(this);
            this->m_gl.createGLControl(this);

            SendMessage(this->m_hWnd, WM_SETFOCUS, 0, 0);
            if (this->m_fileFromArguments != "")
            {
                this->readFile(this->m_fileFromArguments);
            }
            break;
        }
        case WM_SIZE:
        {
            m_tv.resize(196, HIWORD(lParam));
            m_gl.move(200, 0);
            m_gl.resize(LOWORD(lParam) - 200, HIWORD(lParam));
            m_gl.repaint();
            break;
        }
        case WM_PARENTNOTIFY:
        {
            DWORD fwEvent = LOWORD(wParam);
            if (fwEvent == WM_DESTROY)
            {
                ::MessageBox(m_hWnd, "ok", "ok", MB_OK);
            }
            break;
        }
        case WM_NOTIFY:
        {
            NMTREEVIEW *pnmtv = (LPNMTREEVIEW)lParam;
            switch (pnmtv->hdr.code)
            {
                case TVN_SELCHANGED:
                {
                    this->setTexture();
                    break;
                }
            }
            break;
        }
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case MAIN_MENU_FILE_OPEN:
                {
                    this->openFileDialog();
                    break;
                }
                case MAIN_MENU_FILE_CLOSE:
                {
                    ui::TreeViewItem item = this->m_tv.getSelectedItem();
                    if (item.isValid())
                    {
                        ui::TreeViewItem container = item;
                        if (!item.hasChilds())
                            container = item.getParent();

                        if (container.isValid())
                        {
                            TextureContainer *c = (TextureContainer *)container.getData();
                            c->cleanupTextures();
                            container.removeMe();
                            delete c;
                            this->setContainer(NULL);
                        }
                    }
                    break;
                }
                case MAIN_MENU_FILE_QUIT:
                {
                    PostQuitMessage(0);
                    break;
                }
                case MAIN_MENU_HELP_ABOUT:
                {
                    break;
                }
            }
            break;
        }
        case WM_NCDESTROY:
        {
            this->closeAllFiles();
            PostQuitMessage(0);
            break;
        }
    }
    return ::DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}

void Main::openFileDialog()
{
    OPENFILENAME ofn = {0};
    char szFile[MAX_PATH + 1] = {0};
    static char *szFilter = SUPPORTED_FILES_FILTER;

    // specificeer de dialog box zo volledig mogelijk
    ofn.Flags = OFN_HIDEREADONLY;
    ofn.hwndOwner = this->m_hWnd;
    ofn.lpstrCustomFilter = 0;
    ofn.lpstrFile = szFile;
    ofn.lpstrFileTitle = 0;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrInitialDir = 0;
    ofn.lpstrTitle = "HLViewer - Open...";
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.nMaxFile = MAX_PATH;

    if (GetOpenFileName(&ofn) != 0)
    {
        this->readFile(ofn.lpstrFile);
    }
}

void Main::readFile(String filename)
{
    String ext = Common::fileExtention(filename);
    ext.ToLower();

    if (ext == ".wad")
    {
        WadFile *wadfile = new WadFile();

        wadfile->cleanupTextures();
        wadfile->closeFile();

        if (wadfile->openFile(filename))
        {
            this->setContainer(wadfile);
            this->m_gl.useAsCurrent();
            wadfile->setupTextures();
            this->fillTreeView(wadfile);
        }
        else
        {
            MessageBox(this->m_hWnd, wadfile->getLastError(), "Error loading WAD file", MB_OK | MB_ICONEXCLAMATION);
        }
    }
    else if (ext == ".bsp")
    {
        BspFile *bspfile = new BspFile();

        bspfile->cleanupTextures();
        bspfile->closeFile();

        if (bspfile->openFile(filename))
        {
            this->setContainer(bspfile);
            this->m_gl.useAsCurrent();
            bspfile->setupTextures();
            this->fillTreeView(bspfile);
        }
        else
        {
            MessageBox(this->m_hWnd, bspfile->getLastError(), "Error loading BSP file", MB_OK | MB_ICONEXCLAMATION);
        }
    }
    else if (ext == ".mdl")
    {
        MdlFile *mdlfile = new MdlFile();

        mdlfile->cleanupTextures();
        mdlfile->closeFile();

        if (mdlfile->openFile(filename))
        {
            this->setContainer(mdlfile);
            this->m_gl.useAsCurrent();
            mdlfile->setupTextures();
            this->fillTreeView(mdlfile);
        }
        else
        {
            MessageBox(this->m_hWnd, mdlfile->getLastError(), "Error loading MDL file", MB_OK | MB_ICONEXCLAMATION);
        }
    }
    else
    {
        MessageBox(this->m_hWnd, "This file type cannot be loaded yet...", "Unknown filetype", MB_OK | MB_ICONEXCLAMATION);
    }
    this->m_gl.repaint();
}

void Main::closeAllFiles()
{
}

void Main::fillTreeView(TextureContainer *tc)
{
    ui::TreeViewItem root = this->m_tv.addItem(Common::fileName(tc->getFileName()), 0, 0, (DWORD)tc, TVIS_EXPANDED);
    ui::TreeViewItem textures = root.addItem("textures", 0, 0, (DWORD)tc, TVIS_EXPANDED);
    for (int i = 0; i < tc->getTextureCount(); i++)
    {
        int w, h;
        tc->getTextureSize(i, w, h);
        String text = tc->getTextureName(i) + String(" (%dx%d)", w, h);
        textures.addItem(text, 0, 0, i, TVIS_EXPANDED);
    }
}

void Main::setTexture()
{
    ui::TreeViewItem selected = this->m_tv.getSelectedItem();

    if (selected.isValid())
    {
        if (selected.hasChilds())
        {
            TextureContainer* tc = static_cast <TextureContainer *>(selected.getData());
            if (tc != nullptr)
            {
                this->setContainer(tc);
                this->enableMenuItem(MAIN_MENU_TEXTURE, false);
            }
        }
        else
        {
            int index = (int)selected.getData();
            this->m_gl.selectTexture(index);
            this->enableMenuItem(MAIN_MENU_TEXTURE, true);

            this->setContainer((TextureContainer *)selected.getParent().getData());
        }
    }
    else
    {
        this->setContainer((TextureContainer *)selected.getData());
        this->enableMenuItem(MAIN_MENU_TEXTURE, false);
    }
    this->m_gl.setTextureContainer(this->m_currentContainer);
}

void Main::setContainer(TextureContainer *tc)
{
    this->m_currentContainer = tc;
    this->m_gl.setTextureContainer(tc);
    this->enableMenuItem(MAIN_MENU_TEXTURE, false);
    if (tc != 0)
    {
        String windowTitle = (String) "HLViewer - " + this->m_currentContainer->getFileName();
        SetWindowText(this->m_hWnd, (const char *)windowTitle);
    }
    else
    {
        SetWindowText(this->m_hWnd, "HLViewer");
    }
}

HMENU Main::buildMenu()
{
    HMENU menu = CreateMenu();
    MENUITEMINFO mii;

    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_ID | MIIM_STATE | MIIM_STRING | MIIM_DATA | MIIM_SUBMENU;
    mii.fState = MFS_ENABLED;

    mii.dwTypeData = "File";
    mii.hSubMenu = this->buildFileMenu();
    mii.wID = MAIN_MENU_FILE;
    InsertMenuItem(menu, 0, MF_BYCOMMAND, &mii);

    mii.dwTypeData = "Texture";
    mii.hSubMenu = this->buildTextureMenu();
    mii.wID = MAIN_MENU_TEXTURE;
    InsertMenuItem(menu, MAIN_MENU_FILE, MF_BYPOSITION, &mii);

    mii.dwTypeData = "Help";
    mii.hSubMenu = this->buildHelpMenu();
    mii.wID = MAIN_MENU_HELP;
    InsertMenuItem(menu, MAIN_MENU_TEXTURE, MF_BYPOSITION, &mii);

    return menu;
}

HMENU Main::buildFileMenu()
{
    HMENU menu = CreateMenu();
    MENUITEMINFO mii;

    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING | MIIM_FTYPE | MIIM_ID;

    mii.fType = MFT_STRING;
    mii.dwTypeData = "Open file...";
    mii.wID = MAIN_MENU_FILE_OPEN;
    InsertMenuItem(menu, MAIN_MENU_FILE_OPEN, MF_BYCOMMAND, &mii);

    mii.fType = MFT_STRING;
    mii.dwTypeData = "Close";
    mii.wID = MAIN_MENU_FILE_CLOSE;
    InsertMenuItem(menu, MAIN_MENU_FILE_CLOSE, MF_BYCOMMAND, &mii);

    mii.fType = MFT_SEPARATOR;
    InsertMenuItem(menu, 46545, 0, &mii);

    mii.fType = MFT_STRING;
    mii.dwTypeData = "Quit";
    mii.wID = MAIN_MENU_FILE_QUIT;
    InsertMenuItem(menu, MAIN_MENU_FILE_QUIT, MF_BYCOMMAND, &mii);

    return menu;
}

HMENU Main::buildTextureMenu()
{
    HMENU menu = CreateMenu();
    MENUITEMINFO mii;

    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING | MIIM_ID;

    mii.dwTypeData = "Export";
    mii.wID = MAIN_MENU_TEXTURE_EXPORT;
    InsertMenuItem(menu, MAIN_MENU_TEXTURE_EXPORT, MF_BYCOMMAND, &mii);

    return menu;
}

HMENU Main::buildHelpMenu()
{
    HMENU menu = CreateMenu();
    MENUITEMINFO mii;

    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING | MIIM_ID;

    mii.dwTypeData = "About";
    mii.wID = MAIN_MENU_HELP_ABOUT;
    InsertMenuItem(menu, MAIN_MENU_HELP_ABOUT, MF_BYCOMMAND, &mii);

    return menu;
}

void Main::enableMenuItem(UINT item, bool enable)
{
    if (enable)
    {
        EnableMenuItem(this->m_hMenu, item, MFS_ENABLED);
        DrawMenuBar(this->m_hWnd);
    }
    else
    {
        EnableMenuItem(this->m_hMenu, item, MFS_DISABLED | MFS_GRAYED);
        DrawMenuBar(this->m_hWnd);
    }
}
