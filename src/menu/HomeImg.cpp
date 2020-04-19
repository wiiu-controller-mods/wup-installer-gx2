/****************************************************************************
 * Copyright (C) 2017 Dj_Skual
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
#include "HomeImg.h"
#include "MainWindow.h"

HomeImg *HomeImg::homeInstance = NULL;

HomeImg::HomeImg()
	: GuiFrame(150, 150)
	, CThread(CThread::eAttributeAffCore0 | CThread::eAttributePinnedAff)
    , imgData(Resources::GetImageData("home.png"))
	, img(imgData)
	, loaded(false)
	, exitRequested(false)
{   
	mainWindow = Application::instance()->getMainWindow();
	
	this->setPosition(-610, 340);
	this->setAlignment(ALIGN_LEFT | ALIGN_TOP);
	this->append(&img);
	
	resumeThread();
}

HomeImg::~HomeImg()
{
	exitRequested = true;
	shutdownThread();
	this->remove(&img);
	Resources::RemoveImageData(imgData);
}

void HomeImg::Show()
{
	if(!homeInstance)
		homeInstance = new HomeImg;
	
	if(!homeInstance->loaded)
	{
		homeInstance->loaded = true;
		homeInstance->showHomeImg();
	}
	else
	{
		homeInstance->time = 3;
	}
}

void HomeImg::executeThread()
{
	while(!exitRequested)
	{
		suspendThread();
		
		if(loaded)
		{
			startCountdown();
			
			hideHomeImg();
		}
	}
}

void HomeImg::showHomeImg(void)
{
	this->setEffect(EFFECT_FADE, 10, 255);
	this->effectFinished.connect(this, &HomeImg::OnOpenEffectFinish);
	
	mainWindow->append(this);
}

void HomeImg::hideHomeImg()
{
	this->setEffect(EFFECT_FADE, -10, 255);
	this->effectFinished.connect(this, &HomeImg::OnCloseEffectFinish);
}

void HomeImg::startCountdown()
{
	time = 3;
	startTime = OSGetTime();
	u32 passedMs = 0;
	
	while(time)
	{
		passedMs = (OSGetTime() - startTime) * 4000ULL / BUS_SPEED;
		
		if(passedMs >= 1000)
		{
			time--;
			startTime = OSGetTime();
		}
	}
}

void HomeImg::OnOpenEffectFinish(GuiElement *element)
{
	this->effectFinished.disconnect(this);
	
	resumeThread();
}

void HomeImg::OnCloseEffectFinish(GuiElement *element)
{
	this->effectFinished.disconnect(this);
	mainWindow->remove(this);
	loaded = false;
}
