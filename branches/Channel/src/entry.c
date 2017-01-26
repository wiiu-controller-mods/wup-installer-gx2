#include "dynamic_libs/os_functions.h"
#include <string.h>
#include <coreinit/title.h>
#include <nsysnet/socket.h>
#include "common/common.h"
#include "utils/logger.h"
#include "main.h"

int main(int argc, char **argv)
{
	//! do OS (for acquire) and sockets first so we got logging
	InitOSFunctionPointers();
	
	socket_lib_init();
	
	log_init(WUP_LOGGER_IP);
	log_printf("\nStarting WUP Installer GX2 %s\n", WUP_GX2_VERSION);
	
	//!test from where our app is started
	u64 currentTitleID = OSGetTitleID();
	
	if (currentTitleID == 0x000500101004A200 || //! mii maker eur
		currentTitleID == 0x000500101004A100 || //! mii maker usa
		currentTitleID == 0x000500101004A000)	//! mii maker jpn
		return EXIT_SUCCESS;
	
	//! *******************************************************************
	//! *                        Call our Main                            *
	//! *******************************************************************
	Menu_Main();
	
	//! *******************************************************************
	//! *                            Exit                                 *
	//! *******************************************************************
	log_printf("WUP Installer GX2 exit...\n");
	log_deinit();
	
	return EXIT_SUCCESS;
}
