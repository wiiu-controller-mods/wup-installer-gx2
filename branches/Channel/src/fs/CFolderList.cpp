/****************************************************************************
 * Copyright (C) 2011
 * by Dj_Skual
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * CFolderList.cpp
 *
 * for SaveGame Manager GX 2011
 ***************************************************************************/
#include "CFolderList.hpp"
#include "DirList.h"
#include "CFile.hpp"
#include <coreinit/internal.h>

void CFolderList::AddFolder()
{
	FolderStruct * newFolder = new FolderStruct;
	newFolder->name = "";
	newFolder->path = "";
	newFolder->selected = false;
	newFolder->sequence = 0;
	
	Folders.push_back(newFolder);
}

std::string CFolderList::GetName(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return "";

	return Folders.at(ind)->name;
}

std::string CFolderList::GetPath(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return "";

	return Folders.at(ind)->path;
}

bool CFolderList::IsSelected(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return false;

	return Folders.at(ind)->selected;
}

void CFolderList::Select(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return;

	Folders.at(ind)->selected = true;
	AddSequence(ind);
}

void CFolderList::UnSelect(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return;

	Folders.at(ind)->selected = false;
	RemoveSequence(ind);
}

void CFolderList::SelectAll()
{
	if(!Folders.size())
		return;
	
	for(u32 i = 0; i < Folders.size(); i++)
	{
		Folders.at(i)->selected = true;
		AddSequence(i);
	}
}

void CFolderList::UnSelectAll()
{
	if(!Folders.size())
		return;
	
	for(u32 i = 0; i < Folders.size(); i++)
	{
		Folders.at(i)->selected = false;
		Folders.at(i)->sequence = 0;
	}
}

int CFolderList::GetFirstSelected()
{
	if(!Folders.size())
		return -1;
	
	int found = -1;
	for(u32 i = 0; i < Folders.size() && found < 0; i++)
	{
		if(Folders.at(i)->sequence == 1)
			found = i;
	}
	
	return found;
}

void CFolderList::AddSequence(int ind)
{
	if(!Folders.size())
		return;
	
	Folders.at(ind)->sequence = GetSelectedCount();
}

void CFolderList::RemoveSequence(int ind)
{
	if(!Folders.size())
		return;
	
	int removedSequence = Folders.at(ind)->sequence;
	Folders.at(ind)->sequence = 0;
	
	for(u32 i = 0; i < Folders.size(); i++)
	{
		if(Folders.at(i)->sequence > removedSequence)
			Folders.at(i)->sequence = Folders.at(i)->sequence-1;
	}
}

void CFolderList::Click(int ind)
{
	if(ind < 0 || ind >= (int) Folders.size())
		return;

	if(IsSelected(ind))
		UnSelect(ind);
	else
		Select(ind);
}

void CFolderList::Reset()
{
	Folders.clear();
}

int CFolderList::GetSelectedCount()
{
	int selectedCount = 0;
	
	for(u32 i = 0; i < Folders.size(); i++)
	{
		if(Folders.at(i)->selected)
			selectedCount++;
	}
	
	return selectedCount;
}

int CFolderList::Get()
{
	Reset();
	
	DirList dir("fs:/vol/external01/install", NULL, DirList::Dirs);
	
	int cnt = dir.GetFilecount();
	if(cnt > 0)
	{
		int j = 0;
		
		for(int i = 0; i < cnt; i++)
		{
			std::string path = dir.GetFilepath(i);
			path += "/title.tik";
			
			CFile * file = new CFile(path, CFile::ReadOnly);
			
			if(file->isOpen())
			{
				AddFolder();
				Folders.at(j)->name = dir.GetFilename(i);
				Folders.at(j)->path = dir.GetFilepath(i);
				Folders.at(j)->selected = false;
				Folders.at(j)->sequence = 0;
				
				j++;
			}
			
			delete file;
		}
	}
	else
	{
		dir.LoadPath("fs:/vol/external01/install", ".tik", DirList::Files);
		
		cnt = dir.GetFilecount();
		if(cnt > 0)
		{
			AddFolder();
			Folders.at(0)->name = "install";
			Folders.at(0)->path = "fs:/vol/external01/install";
			Folders.at(0)->selected = false;
			Folders.at(0)->sequence = 0;
		}
	}
	
	return Folders.size();
}
