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
#include "dynamic_libs/os_functions.h"
#include "utils/logger.h"
#include "power.h"

bool isEnabledAutoPowerDown()
{
	bool enabled = false;
	int apd_enabled = 0;
	
	IMIsAPDEnabled(&apd_enabled);
	
	if(apd_enabled)
	{
		enabled = true;
		log_printf("Auto Power Down enabled\n");
	}
	
	return enabled;
}

bool disableAutoPowerDown()
{
	bool res = false;
	
	if(IMDisableAPD() == 0) //!APD disabled
	{
		res = true;
		log_printf("Auto Power Down disabled\n");
	}
	
	return res;
}

bool enableAutoPowerDown()
{
	bool res = false;
	
	if(IMEnableAPD() == 0) //!APD enabled
	{
		res = true;
		log_printf("Auto Power Down re-enabled\n");
	}
	
	return res;
}
