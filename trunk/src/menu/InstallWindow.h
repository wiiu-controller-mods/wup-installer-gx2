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
    sigslot::signal1<GuiElement *> installWindowClosed;
	
private:
    void OnValidInstallClick(GuiElement * element, int val);
    void OnDestinationChoice(GuiElement * element, int choice);
	void OnCloseWindow(GuiElement * element, int val);
	void OnWindowClosed(GuiElement * element);
	void OnOpenEffectFinish(GuiElement *element);
	void OnCloseEffectFinish(GuiElement *element);
	
	void executeThread();
	void InstallProcess();
	
	GuiFrame * drcFrame;
	//GuiFrame * tvFrame;
    
    CFolderList * folderList;
	
	MessageBox * messageBox;
	
	MainWindow * mainWindow;
	
	int folderCount;
};

#endif
