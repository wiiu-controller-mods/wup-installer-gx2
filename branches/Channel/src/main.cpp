#include "Application.h"
#include "dynamic_libs/padscore_functions.h"
#include "system/memory.h"
#include "utils/logger.h"

/* Entry point */
extern "C" int Menu_Main(void)
{
	//!*******************************************************************
	//!                   Initialize function pointers                   *
	//!*******************************************************************
	InitPadScoreFunctionPointers();
	
	log_printf("Function exports loaded\n");
	
	//!*******************************************************************
	//!                    Initialize heap memory                        *
	//!*******************************************************************
	log_print("Initialize memory management\n");
	memoryInitialize();
	
	//!*******************************************************************
	//!                    Enter main application                        *
	//!*******************************************************************
	log_printf("Start main application\n");
	Application::instance()->exec();
	log_printf("Main application stopped\n");
	
	Application::destroyInstance();
	
	return 0;
}
