#ifndef INSTALL_WINDOW_H_
#define INSTALL_WINDOW_H_

#include "fs/CFolderList.hpp"
#include "gui/MessageBox.h"

class MainWindow;

class InstallWindow : public GuiFrame, public CThread, public sigslot::has_slots<>
{
public:
    InstallWindow(CFolderList * list);
	~InstallWindow();
	
    void startInstalling()
    {
        resumeThread();
    }

    //sigslot::signal0<> updateFolderList;
    sigslot::signal1<GuiElement *> closeInstallWindow;
	
private:
    void executeThread();
	
	void OnValidInstallClick(GuiElement * element, int val);
	void OnCloseWindow(GuiElement * element, int val);
	void InstallProcess();
    
    CFolderList * folderList;
	
	MessageBox * messageBox;
	
	MainWindow * mainWindow;
	
	int folderCount;
};

#endif
