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

#define MAX_FOLDERS_PER_PAGE 3

BrowserWindow::BrowserWindow(int w, int h, CFolderList * list)
    : GuiFrame(w, h)
	, scrollbar(h - 150)
    , buttonClickSound(Resources::GetSound("button_click.wav"))
    , buttonImageData(Resources::GetImageData("choiceUncheckedRectangle.png"))
    , buttonCheckedImageData(Resources::GetImageData("choiceCheckedRectangle.png"))
    , buttonHighlightedImageData(Resources::GetImageData("choiceSelectedRectangle.png"))
    , touchTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::VPAD_TOUCH)
    //, wpadTouchTrigger(GuiTrigger::CHANNEL_2 | GuiTrigger::CHANNEL_3 | GuiTrigger::CHANNEL_4 | GuiTrigger::CHANNEL_5, GuiTrigger::BUTTON_A)
    , buttonATrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_A, true)
    , buttonUpTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_UP | GuiTrigger::STICK_L_UP, true)
    , buttonDownTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::BUTTON_DOWN | GuiTrigger::STICK_L_DOWN, true)
    , DPADButtons(w,h)
    , AButton(w,h)
{
	folderList = list;
	currentYOffset = 0;
	
    buttonCount = folderList->GetCount();
	folderButtons.resize(buttonCount);
	
	for(int i = 0; i < buttonCount; i++)
	{      
		folderButtons[i].folderButtonImg = new GuiImage(buttonImageData);
		folderButtons[i].folderButtonCheckedImg = new GuiImage(buttonCheckedImageData);
		folderButtons[i].folderButtonHighlightedImg = new GuiImage(buttonHighlightedImageData);
		folderButtons[i].folderButton = new GuiButton(folderButtons[i].folderButtonImg->getWidth(), folderButtons[i].folderButtonImg->getHeight());
		folderButtons[i].folderButtonText = new GuiText(folderList->GetName(i).c_str(), 42, glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		
		folderButtons[i].folderButton->setImageSelectOver(folderButtons[i].folderButtonHighlightedImg);
		folderButtons[i].folderButton->setLabel(folderButtons[i].folderButtonText);
		folderButtons[i].folderButton->setSoundClick(buttonClickSound);
		folderButtons[i].folderButton->setImage(folderButtons[i].folderButtonImg);
		
		folderButtons[i].folderButton->setPosition(0, 150 - (folderButtons[i].folderButtonImg->getHeight() + 30) * i);
		folderButtons[i].folderButton->setAlignment(ALIGN_LEFT | ALIGN_MIDDLE);
        folderButtons[i].folderButton->setTrigger(&touchTrigger);
		//folderButtons[i].folderButton->setTrigger(&wpadTouchTrigger);
		folderButtons[i].folderButton->clicked.connect(this, &BrowserWindow::OnFolderButtonClick);
		this->append(folderButtons[i].folderButton);
	}
	
	if(buttonCount > MAX_FOLDERS_PER_PAGE)
    {
		scrollbar.SetPageSize((buttonImageData->getHeight() + 30) * (buttonCount - MAX_FOLDERS_PER_PAGE));
        scrollbar.SetEntrieCount((buttonImageData->getHeight() + 30) * (buttonCount - MAX_FOLDERS_PER_PAGE));
        scrollbar.setAlignment(ALIGN_RIGHT | ALIGN_MIDDLE);
        scrollbar.setPosition(0, -30);
        scrollbar.listChanged.connect(this, &BrowserWindow::OnScrollbarListChange);
        this->append(&scrollbar);
    }
	
	DPADButtons.setTrigger(&buttonUpTrigger);
    DPADButtons.setTrigger(&buttonDownTrigger);
    DPADButtons.clicked.connect(this, &BrowserWindow::OnDPADClick);
	this->append(&DPADButtons);
    
	AButton.setTrigger(&buttonATrigger);
    AButton.clicked.connect(this, &BrowserWindow::OnAButtonClick);
	this->append(&AButton);
	
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
   
    Resources::RemoveImageData(buttonImageData);
    Resources::RemoveImageData(buttonCheckedImageData);
    Resources::RemoveSound(buttonClickSound);
}

void BrowserWindow::UpdateFolderButton(int ind)
{
	if(folderList->IsSelected(ind))   
		folderButtons[ind].folderButton->setImage(folderButtons[ind].folderButtonCheckedImg);
	else
		folderButtons[ind].folderButton->setImage(folderButtons[ind].folderButtonImg);
}

void BrowserWindow::OnFolderButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger)
{	
	int index = -1;
	for(int i = 0; i < buttonCount; i++)
	{
		if(folderButtons[i].folderButton == button)
		{
			index = i;
			
			if(folderList->IsSelected(i))
				folderList->UnSelect(i);
			else
				folderList->Select(i);
		}
		else
			folderButtons[i].folderButton->clearState(STATE_SELECTED);
	}
	
	UpdateFolderButton(index);
}

int BrowserWindow::SearchSelectedButton()
{
	int index = -1;
	for(int i = 0; i < buttonCount && index < 0; i++)
	{
		if(folderButtons[i].folderButton->getState() == STATE_SELECTED)
			index = i;
	}
	
	return index;
}

void BrowserWindow::OnAButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger)
{
	int index = SearchSelectedButton();
	
	if(index < 0)
		return;
	
	if(folderList->IsSelected(index))
		folderList->UnSelect(index);
	else
		folderList->Select(index);
	
	UpdateFolderButton(index);
}

void BrowserWindow::OnDPADClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger)
{
	int index = SearchSelectedButton();
	
	if(index < 0 && trigger == &buttonUpTrigger)
		return;
	
	if(trigger == &buttonUpTrigger && index > 0)
	{
		folderButtons[index].folderButton->clearState(STATE_SELECTED);
		index--;
		folderButtons[index].folderButton->setState(STATE_SELECTED);
	}
	else if(trigger == &buttonDownTrigger && index < buttonCount-1)
	{
		if(index >= 0)
			folderButtons[index].folderButton->clearState(STATE_SELECTED);
		index++;
		folderButtons[index].folderButton->setState(STATE_SELECTED);
	}
	
	scrollbar.SetSelectedItem((buttonImageData->getHeight() + 30) * index);
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
