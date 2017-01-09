#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "common/common.h"
#include "utils/logger.h"
#include "main.h"

int __entry_menu(int argc, char **argv)
{
	//! do OS (for acquire) and sockets first so we got logging
	InitOSFunctionPointers();
	InitSocketFunctionPointers();
	
	log_init(WUP_LOGGER_IP);
	log_print("Starting WUP Installer GX2 " WUP_GX2_VERSION "\n");
	
	InitSysFunctionPointers();
	
	//! *******************************************************************
	//! *                        Call our Main                            *
	//! *******************************************************************
	Menu_Main();
	
	//! *******************************************************************
	//! *                 Jump to homebrew launcher                       *
	//! *******************************************************************
	log_deinit();
	
	return EXIT_SUCCESS;
}
