/****************************************************************************
 * Copyright (C) 2015 Dimok
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
#include "BrowserWindow.h"
#include "utils/StringTools.h"
#include "fs/DirList.h"

#define MAX_FOLDERS_PER_PAGE 3

BrowserWindow::BrowserWindow(int w, int h)
    : GuiFrame(w, h)
	, scrollbar(h - 150)
    , buttonClickSound(Resources::GetSound("button_click.wav"))
    , titleImageData(Resources::GetImageData("titleHeader.png"))
    , titleImage(titleImageData)
	, buttonImageData(Resources::GetImageData("choiceUncheckedRectangle.png"))
    , buttonCheckedImageData(Resources::GetImageData("choiceCheckedRectangle.png"))
    , buttonHighlightedImageData(Resources::GetImageData("choiceSelectedRectangle.png"))
    , touchTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::VPAD_TOUCH)
    //, wpadTouchTrigger(GuiTrigger::CHANNEL_2 | GuiTrigger::CHANNEL_3 | GuiTrigger::CHANNEL_4 | GuiTrigger::CHANNEL_5, GuiTrigger::BUTTON_A)
    , buttonATrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_A, true)
    , buttonUpTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_UP | GuiTrigger::STICK_L_UP, true)
    , buttonDownTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_DOWN | GuiTrigger::STICK_L_DOWN, true)
    //, buttonLeftTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_LEFT | GuiTrigger::STICK_L_LEFT, true)
    //, buttonRightTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_RIGHT | GuiTrigger::STICK_L_RIGHT, true)
    , DPADButtons(w,h)
    , selectedButtonDPAD(-1)	
{
	currentYOffset = 0;
	
    titleText.setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    titleText.setFontSize(46);
    titleText.setPosition(0, 10);
    titleText.setBlurGlowColor(5.0f, glm::vec4(0.0, 0.0, 0.0f, 1.0f));
    titleText.setText("WUP Installer GX2");
    titleImage.setPosition(0, 310);
	
	DirList dir("sd:/install", NULL, DirList::Dirs);
	
	buttonCount = dir.GetFilecount();
	if(buttonCount > 0)
	{
		folderButtons.resize(buttonCount);
		
		for(int i = 0; i < buttonCount; i++)
		{      
			folderButtons[i].folderButtonImg = new GuiImage(buttonImageData);
			folderButtons[i].folderButtonCheckedImg = new GuiImage(buttonCheckedImageData);
			folderButtons[i].folderButtonHighlightedImg = new GuiImage(buttonHighlightedImageData);
			folderButtons[i].folderButton = new GuiButton(folderButtons[i].folderButtonImg->getWidth(), folderButtons[i].folderButtonImg->getHeight());
			folderButtons[i].folderButtonText = new GuiText(dir.GetFilename(i), 42, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
			
			folderButtons[i].folderButton->setImageSelectOver(folderButtons[i].folderButtonHighlightedImg);
			folderButtons[i].folderButton->setLabel(folderButtons[i].folderButtonText);
			folderButtons[i].folderButton->setSoundClick(buttonClickSound);
			folderButtons[i].folderButton->setImage(folderButtons[i].folderButtonImg);
			
			folderButtons[i].folderButton->setPosition(0, 150 - (folderButtons[i].folderButtonImg->getHeight() + 30) * i);
			folderButtons[i].folderButton->setEffectGrow();
			folderButtons[i].folderButton->setTrigger(&touchTrigger);
			//folderButtons[i].folderButton->setTrigger(&wpadTouchTrigger);
			folderButtons[i].folderButton->clicked.connect(this, &BrowserWindow::OnFolderButtonClick);
			browserFrame.append(folderButtons[i].folderButton);
			
			folderButtons[i].selected = false;
			folderButtons[i].path = dir.GetFilepath(i);
		}
	}
	else
	{
		dir.LoadPath("sd:/install", ".tik", DirList::Files);
		
		buttonCount = dir.GetFilecount();
		if(buttonCount > 0)
		{
			folderButtons.resize(1);
			
			folderButtons[0].folderButtonImg = new GuiImage(buttonImageData);
			folderButtons[0].folderButtonCheckedImg = new GuiImage(buttonCheckedImageData);
			folderButtons[0].folderButtonHighlightedImg = new GuiImage(buttonHighlightedImageData);
			folderButtons[0].folderButton = new GuiButton(folderButtons[0].folderButtonImg->getWidth(), folderButtons[0].folderButtonImg->getHeight());
			folderButtons[0].folderButtonText = new GuiText("install", 42, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
			
			folderButtons[0].folderButton->setImageSelectOver(folderButtons[0].folderButtonHighlightedImg);
			folderButtons[0].folderButton->setLabel(folderButtons[0].folderButtonText);
			folderButtons[0].folderButton->setSoundClick(buttonClickSound);
			folderButtons[0].folderButton->setImage(folderButtons[0].folderButtonImg);
			
			folderButtons[0].folderButton->setPosition(0, 150);
			folderButtons[0].folderButton->setEffectGrow();
			folderButtons[0].folderButton->setTrigger(&touchTrigger);
			//folderButtons[0].folderButton->setTrigger(&wpadTouchTrigger);
			folderButtons[0].folderButton->clicked.connect(this, &BrowserWindow::OnFolderButtonClick);
			browserFrame.append(folderButtons[0].folderButton);
			
			folderButtons[0].selected = false;
			folderButtons[0].path = "sd:/install";
		}
	}
	
	if(buttonCount > MAX_FOLDERS_PER_PAGE)
    {
		scrollbar.SetPageSize((buttonImageData->getHeight() + 30) * (buttonCount - MAX_FOLDERS_PER_PAGE));
        scrollbar.SetEntrieCount((buttonImageData->getHeight() + 30) * (buttonCount - MAX_FOLDERS_PER_PAGE));
        scrollbar.setAlignment(ALIGN_CENTER | ALIGN_MIDDLE);
        scrollbar.setPosition(500, -30);
        scrollbar.listChanged.connect(this, &BrowserWindow::OnScrollbarListChange);
        browserFrame.append(&scrollbar);
    }
	
	//! append on top
	append(&browserFrame);
	browserFrame.append(&titleImage);
    browserFrame.append(&titleText);
	titleText.setParent(&titleImage);
	
    DPADButtons.setTrigger(&buttonATrigger);
    DPADButtons.setTrigger(&buttonUpTrigger);
    DPADButtons.setTrigger(&buttonDownTrigger);
    DPADButtons.clicked.connect(this, &BrowserWindow::OnDPADClick);
    
	browserFrame.append(&DPADButtons);
}

BrowserWindow::~BrowserWindow()
{
    for(u32 i = 0; i < folderButtons.size(); ++i)
    {
        delete folderButtons[i].folderButtonImg;
        delete folderButtons[i].folderButtonCheckedImg;
        delete folderButtons[i].folderButtonHighlightedImg;
        delete folderButtons[i].folderButton;
        delete folderButtons[i].folderButtonText;
    }
   
    Resources::RemoveImageData(titleImageData);
    Resources::RemoveImageData(buttonImageData);
    Resources::RemoveImageData(buttonCheckedImageData);
    Resources::RemoveSound(buttonClickSound);
}

void BrowserWindow::UpdateFolderButtons()
{
	for(int i = 0; i < buttonCount; i++)
    {
		if(i == selectedButtonDPAD)
			folderButtons[i].folderButton->setState(STATE_SELECTED);
		else
			folderButtons[i].folderButton->clearState(STATE_SELECTED);
		
        if(folderButtons[i].selected == true)   
			folderButtons[i].folderButton->setImage(folderButtons[i].folderButtonCheckedImg);
        else
			folderButtons[i].folderButton->setImage(folderButtons[i].folderButtonImg);
    }
}

void BrowserWindow::OnFolderButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger)
{	
	for(int i = 0; i < buttonCount; i++)
	{
		if(folderButtons[i].folderButton == button)
		{
			folderButtons[i].selected = !folderButtons[i].selected;
			
			selectedButtonDPAD = i;
		}
	}
	
	UpdateFolderButtons();
}

void BrowserWindow::OnDPADClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger)
{
	if(trigger == &buttonATrigger)
	{
        if(selectedButtonDPAD >= 0 && selectedButtonDPAD < buttonCount)
		{
			int i = selectedButtonDPAD;
			folderButtons[i].selected = !folderButtons[i].selected;
		}
	}
	else if(trigger == &buttonUpTrigger)
	{
		selectedButtonDPAD--;
		if(selectedButtonDPAD < 0)
			selectedButtonDPAD = 0;
	}
	else if(trigger == &buttonDownTrigger)
	{
		selectedButtonDPAD++;
		if(selectedButtonDPAD >= buttonCount)
			selectedButtonDPAD = buttonCount - 1;
	}
	
	UpdateFolderButtons();
	scrollbar.SetSelectedItem((buttonImageData->getHeight() + 30) * selectedButtonDPAD);
}
	
void BrowserWindow::OnScrollbarListChange(int selectItem, int pageIndex)
{
    currentYOffset = selectItem + pageIndex;

    for(int i = 0; i < buttonCount; i++)
    {
        folderButtons[i].folderButton->setPosition(0, 150 - (folderButtons[i].folderButtonImg->getHeight() + 30) * i + currentYOffset);
    }
}

/*void BrowserWindow::OnSubMenuCloseClicked(GuiElement *element)
{
    //! disable element for triggering buttons again
    element->setState(GuiElement::STATE_DISABLED);
    element->setEffect(EFFECT_FADE, -10, 0);
    element->effectFinished.connect(this, &SettingsLanguageMenu::OnSubMenuCloseEffectFinish);

    //! fade in category selection
    languageFrame.setEffect(EFFECT_FADE, 10, 255);
    append(&languageFrame);
}*/

/*void BrowserWindow::OnSubMenuOpenEffectFinish(GuiElement *element)
{
    //! make element clickable again
    element->clearState(GuiElement::STATE_DISABLED);
    element->effectFinished.disconnect(this);
    //! remove category selection from settings
    remove(&languageFrame);
}*/

/*void BrowserWindow::OnSubMenuCloseEffectFinish(GuiElement *element)
{
    remove(element);
    AsyncDeleter::pushForDelete(element);

    //! enable all elements again
    languageFrame.clearState(GuiElement::STATE_DISABLED);
}*/
