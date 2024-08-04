/* 
 * File:   Main.h
 * Author: Wouter
 *
 * Created on June 24, 2008, 1:57 PM
 */

#ifndef _MAIN_H_
#define	_MAIN_H_

#include "texturecontainer.h"
#include "Common/common.h"
#include "window.h"
#include "treeview.h"
#include "listview.h"
#include "containerview.h"
#include "wadfile.h"
#include "bspfile.h"
#include "mdlfile.h"

#define MAIN_MENU_FILE 1
#define MAIN_MENU_FILE_OPEN 11
#define MAIN_MENU_FILE_CLOSE 12
#define MAIN_MENU_FILE_QUIT 13

#define MAIN_MENU_TEXTURE 2
#define MAIN_MENU_TEXTURE_EXPORT 21

#define MAIN_MENU_HELP 3
#define MAIN_MENU_HELP_ABOUT 31

#define SUPPORTED_FILES_FILTER "Supported Files(*.bsp *.mdl *.wad)\0*.wad;*.bsp;*.mdl\0WAD Files(*.wad)\0*.wad\0BSP Files(*.bsp)\0*.bsp\0MDL Files(*.mdl)\0*.mdl\0"

class Main : public ui::Window
{
public:
    Main(int argc, char* argv[]);
    virtual ~Main();
 
protected:
    virtual LRESULT objectProc(UINT msg, WPARAM wParam, LPARAM lParam);
    HMENU buildMenu();
    HMENU buildFileMenu();
    HMENU buildTextureMenu();
    HMENU buildHelpMenu();
    void enableMenuItem(UINT item, bool enable);

    void openFileDialog();
    void readFile(String filename);
    void closeAllFiles();
    void fillTreeView(TextureContainer* tc);

    void setTexture();
    void setContainer(TextureContainer* tc);

    void parseArgs(int argc, char* argv[]);
    
protected:
    ui::TreeView m_tv;
    ContainerView m_gl;

    TextureContainer* m_currentContainer;

    String m_fileFromArguments;

};

#endif	/* _MAIN_H_ */

