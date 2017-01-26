#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "common/retain_vars.h"
#include "common/common.h"
#include "utils/logger.h"
#include "main.h"

static volatile u64 currentTitleID = 0;

int __entry_menu(int argc, char **argv)
{
	//! do OS (for acquire) and sockets first so we got logging
	InitOSFunctionPointers();
	InitSocketFunctionPointers();
	
	log_init(WUP_LOGGER_IP);
	log_printf("\nStarting WUP Installer GX2 %s\n", WUP_GX2_VERSION);
	
	InitSysFunctionPointers();
	
	//! *******************************************************************
	//! *           Check from where our application is started           *
	//! *******************************************************************
	if(gMode == WUP_MODE_UNKNOW)
	{
		currentTitleID = OSGetTitleID();
		
		if (currentTitleID == 0x000500101004A200 || //! mii maker eur
			currentTitleID == 0x000500101004A100 || //! mii maker usa
			currentTitleID == 0x000500101004A000)	//! mii maker jpn
			gMode = WUP_MODE_MII_MAKER;
		else			   //!0x0005000013374842	//! hbl channel
			gMode = WUP_MODE_HBC;
	}
	
	//! *******************************************************************
	//! *                        Call our Main                            *
	//! *******************************************************************
	Menu_Main();
	
	int result = EXIT_SUCCESS;
	
	if(gMode == WUP_MODE_MII_MAKER_INSTALL)
	{
		SYSLaunchMenu();
		
		result = EXIT_RELAUNCH_ON_LOAD;
	}
	else if(gMode == WUP_MODE_MII_MAKER_FINISH)
	{
		gMode = WUP_MODE_MII_MAKER;
		
		SYSLaunchTitle(currentTitleID);
		
		result = EXIT_RELAUNCH_ON_LOAD;
	}
	
	//! *******************************************************************
	//! *                 Jump to homebrew launcher                       *
	//! *******************************************************************
	log_deinit();
	
	return result;
}
