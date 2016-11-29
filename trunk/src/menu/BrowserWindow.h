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
#ifndef _BROWSERWINDOW_H_
#define _BROWSERWINDOW_H_

#include "gui/Gui.h"
#include "gui/Scrollbar.h"

class BrowserWindow : public GuiFrame, public sigslot::has_slots<>
{
public:
    BrowserWindow(int w, int h);
    virtual ~BrowserWindow();
	
private:
    void OnFolderButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger);
	void OnDPADClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger);	
	void UpdateFolderButtons();
	
	void OnScrollbarListChange(int selectItem, int pageIndex);
	
	GuiFrame browserFrame;
	
	Scrollbar scrollbar;
	
    GuiSound *buttonClickSound;
    
	GuiText titleText;
    GuiImageData *titleImageData;
    GuiImage titleImage;
	
	GuiImageData *buttonImageData;
    GuiImageData *buttonCheckedImageData;
    GuiImageData *buttonHighlightedImageData;
	
    GuiTrigger touchTrigger;
    //GuiTrigger wpadTouchTrigger;
    GuiTrigger buttonATrigger;
    
    GuiTrigger buttonUpTrigger;
    GuiTrigger buttonDownTrigger;
    //GuiTrigger buttonLeftTrigger;
    //GuiTrigger buttonRightTrigger;

    GuiButton DPADButtons;
	
	int selectedButtonDPAD;
	int currentYOffset;
	int buttonCount;
	
    typedef struct
    {
        GuiImage *folderButtonImg;
        GuiImage *folderButtonCheckedImg;
        GuiImage *folderButtonHighlightedImg;
        GuiButton *folderButton;
        GuiText *folderButtonText;
		std::string path;
		bool selected;
    } FolderButton;

    std::vector<FolderButton> folderButtons;
};

#endif //_BROSERWINDOW_H_
