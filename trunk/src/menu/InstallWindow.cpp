/****************************************************************************
 * Copyright (C) 2011 Dimok
 * Copyright (C) 2012 Cyan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "Application.h"
#include "InstallWindow.h"
#include "MainWindow.h"
#include "utils/StringTools.h"

InstallWindow::InstallWindow(CFolderList * list)
	: GuiFrame(0, 0)
	, CThread(CThread::eAttributeAffCore0 | CThread::eAttributePinnedAff)
	, folderList(list)
{   
	mainWindow = Application::instance()->getMainWindow();
	
	folderCount = folderList->GetSelectedCount();
	
	if(folderCount > 0)
	{
		std::string message = fmt("%d application(s)", folderCount);
		messageBox = new MessageBox(MessageBox::BT_YESNO, MessageBox::IT_ICONQUESTION, false);
		messageBox->setTitle("Are you sure you want to install:");
		messageBox->setMessage1(message);
		messageBox->messageYesClicked.connect(this, &InstallWindow::OnValidInstallClick);
		messageBox->messageNoClicked.connect(this, &InstallWindow::OnCloseWindow);
	}
	else
	{
		messageBox = new MessageBox(MessageBox::BT_OK, MessageBox::IT_ICONEXCLAMATION, false);
		messageBox->setTitle("No content selected.");
		messageBox->setMessage1("Return to folder browser.");
		messageBox->messageOkClicked.connect(this, &InstallWindow::OnCloseWindow);
	}
	
	drcFrame = new GuiFrame(0, 0);
	drcFrame->setEffect(EFFECT_FADE, 10, 255);
	drcFrame->setState(GuiElement::STATE_DISABLED);
	drcFrame->effectFinished.connect(this, &InstallWindow::OnOpenEffectFinish);
	drcFrame->append(messageBox);
	
	mainWindow->appendDrc(drcFrame);
}

InstallWindow::~InstallWindow()
{
	drcFrame->remove(messageBox);
	mainWindow->remove(drcFrame);
	delete drcFrame;
	delete messageBox;
}

void InstallWindow::OnValidInstallClick(GuiElement * element, int val)
{
	messageBox->messageYesClicked.disconnect(this);
	messageBox->messageNoClicked.disconnect(this);
	messageBox->reload("Where do you want to install?", "", "", MessageBox::BT_DEST, MessageBox::IT_ICONQUESTION);
	messageBox->messageYesClicked.connect(this, &InstallWindow::OnDestinationChoice);
	messageBox->messageNoClicked.connect(this, &InstallWindow::OnDestinationChoice);
}

void InstallWindow::OnDestinationChoice(GuiElement * element, int choice)
{
	if(choice == MessageBox::MR_YES)
		target = NAND;
	else
		target = USB;
	
	Application::instance()->exitDisable();
	
	messageBox->messageYesClicked.disconnect(this);
	messageBox->messageNoClicked.disconnect(this);
	
	startInstalling();
}

void InstallWindow::executeThread()
{
	canceled = false;
	
	int total = folderList->GetSelectedCount();
	int pos = 1;
	
	while(pos <= total && !canceled)
	{
		InstallProcess(pos, total);
		
		if(pos < total)
		{
			int time = 6;
			u64 startTime = OSGetTime();
			u32 passedMs = 0;
			
			while(time && !canceled)
			{
				passedMs = (OSGetTime() - startTime) * 4000ULL / BUS_SPEED;
				
				if(passedMs >= 1000)
				{
					time--;
					startTime = OSGetTime();
					messageBox->setMessage2(fmt("Starting next installation in %d second(s)", time));
				}
			}
		}
		
		pos++;
	}
	
	Application::instance()->exitEnable();
}

void InstallWindow::InstallProcess(int pos, int total)
{
	int index = folderList->GetFirstSelected();
	
	std::string title = fmt("Installing... (%d/%d)", pos, total);
	std::string gameName = folderList->GetName(index);
	
	messageBox->reload(title, gameName, "", MessageBox::BT_NOBUTTON, MessageBox::IT_ICONINFORMATION, true, "0.0 %");
	
	/////////////////////////////
	// install process
	sleep(5);
	
	/////////////////////////////
	
	if(pos == total)
	{
		messageBox->reload("Succesfully installed", gameName, "", MessageBox::BT_OK, MessageBox::IT_ICONTRUE);
		messageBox->messageOkClicked.connect(this, &InstallWindow::OnCloseWindow);
	}
	else
	{
		messageBox->reload("Succesfully installed", gameName, "Starting next installation in 6 second(s)", MessageBox::BT_CANCEL, MessageBox::IT_ICONTRUE);
		messageBox->messageCancelClicked.connect(this, &InstallWindow::OnInstallProcessCancel);
	}
	
	folderList->UnSelect(index);
}

void InstallWindow::OnInstallProcessCancel(GuiElement *element, int val)
{
	canceled = true;
	OnCloseWindow(this, 0);//////////////////////
}

void InstallWindow::OnCloseWindow(GuiElement * element, int val)
{
	messageBox->setEffect(EFFECT_FADE, -10, 255);
    messageBox->setState(GuiElement::STATE_DISABLED);
    messageBox->effectFinished.connect(this, &InstallWindow::OnWindowClosed);
	
	
}

void InstallWindow::OnWindowClosed(GuiElement *element)
{
	messageBox->effectFinished.disconnect(this);
	installWindowClosed(this);
	AsyncDeleter::pushForDelete(this);
}

void InstallWindow::OnOpenEffectFinish(GuiElement *element)
{
	element->effectFinished.disconnect(this);
    element->clearState(GuiElement::STATE_DISABLED);
}

void InstallWindow::OnCloseEffectFinish(GuiElement *element)
{
	remove(element);
    AsyncDeleter::pushForDelete(element);
}
