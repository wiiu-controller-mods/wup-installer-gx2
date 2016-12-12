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
		messageBox->setMessage(message);
		messageBox->messageYesClicked.connect(this, &InstallWindow::OnValidInstallClick);
		messageBox->messageNoClicked.connect(this, &InstallWindow::OnCloseWindow);
	}
	else
	{
		messageBox = new MessageBox(MessageBox::BT_OK, MessageBox::IT_ICONEXCLAMATION, false);
		messageBox->setTitle("No content selected.");
		messageBox->setMessage("Return to folder browser.");
		messageBox->messageOkClicked.connect(this, &InstallWindow::OnCloseWindow);
	}
	
	mainWindow->appendDrc(messageBox);
}

InstallWindow::~InstallWindow()
{
	mainWindow->remove(messageBox);
	delete messageBox;
}

void InstallWindow::OnValidInstallClick(GuiElement * element, int val)
{
	closeInstallWindow(this);//
	//choisir nand ou usb
}

void InstallWindow::OnCloseWindow(GuiElement * element, int val)
{
	element->setEffect(EFFECT_FADE, -10, 255);
    element->setState(GuiElement::STATE_DISABLED);
    
	closeInstallWindow(this);
}

void InstallWindow::executeThread()
{
	/*MissingImagesCount = 0;
	
	messageBox.setTitle(tr("Download 3D Covers"));
	
	FindMissingImages();

	if(MissingImagesCount == 0)
	{
	    log_printf("No images missing\n");
        asyncLoadFinished(this, MissingImages.size());
		return;
	}

	u32 TotalDownloadCount = MissingImagesCount;

	messageBox.setMessage(tr("Connecting.."));
	
	DownloadProcess(TotalDownloadCount);*/
	
	//////////////////////////////////
	
	//log_printf("OK!!\n");

	OnCloseWindow(this, 0);
}

void InstallWindow::InstallProcess()
{
	/*for(u32 i = 0, pos = 1; i < MissingImages.size(); ++i, ++pos)
	{
		//if(ProgressCanceled())
		//	break;

        //snprintf(progressMsg, sizeof(progressMsg), "http://gametdb.com : %s.png", MissingImages[i].gameID.c_str());

		//ShowProgress(MissingImages[i].progressTitle, fmt("%i %s", TotalDownloadCount - pos, tr( "files left" )), progressMsg, pos, TotalDownloadCount);
		
		char buffer[100];
		snprintf(buffer,sizeof(buffer), "%d", TotalDownloadCount - pos);
        
		string progressMsg = "http://gametdb.com :";
		progressMsg += " ";
		progressMsg += MissingImages[i].gameID.c_str();
		progressMsg += ".png";
		progressMsg += " - ";
		progressMsg += std::string(buffer);
		progressMsg += " ";
		progressMsg += tr("files left.");
		
		messageBox.setInfo(progressMsg.c_str());
		
		
        messageBox.setProgress(100.0f * (f32)pos / (f32)TotalDownloadCount);

        std::string imageData;

		DownloadImage(MissingImages[i].downloadURL, MissingImages[i].gameID.c_str(), MissingImages[i].fileExt, imageData);
		if(!imageData.size())
		{
			if(MissingImages[i].backupURL)
			{
				log_printf("Trying backup URL.\n");
				MissingImages[i].downloadURL = MissingImages[i].backupURL;
				MissingImages[i].backupURL = NULL;
				--i;
				--pos;
			}
			continue;
		}

		log_printf(" - OK\n");

		std::string strOutpath;
		strOutpath = MissingImages[i].writepath;
		strOutpath += "/";
		strOutpath += MissingImages[i].gameID;
		strOutpath += MissingImages[i].fileExt;

		CFile file(strOutpath, CFile::WriteOnly);
		if(file.isOpen())
        {
			file.write((u8*)imageData.c_str(), imageData.size());
            file.close();
        }

		//! Remove the image from the vector since it's done
		MissingImages.erase(MissingImages.begin()+i);
		--i;
	}

	return MissingImages.size();*/
}
