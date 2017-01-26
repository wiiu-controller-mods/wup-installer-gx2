#include "Application.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"

/* Entry point */
extern "C" int Menu_Main(void)
{
    //!*******************************************************************
    //!                   Initialize function pointers                   *
    //!*******************************************************************
    InitFSFunctionPointers();
    InitGX2FunctionPointers();
    InitVPadFunctionPointers();
    InitPadScoreFunctionPointers();
    InitAXFunctionPointers();

    log_print("Function exports loaded\n");

    //!*******************************************************************
    //!                    Initialize heap memory                        *
    //!*******************************************************************
    log_print("Initialize memory management\n");
    memoryInitialize();

    //!*******************************************************************
    //!                        Initialize FS                             *
    //!*******************************************************************
    log_printf("Mount SD partition\n");
    mount_sd_fat("sd");

    //!*******************************************************************
    //!                    Enter main application                        *
    //!*******************************************************************
    log_printf("Start main application\n");
    Application::instance()->exec();
    log_printf("Main application stopped\n");

    Application::destroyInstance();

    log_printf("Unmount SD\n");
    unmount_sd_fat("sd");
    
	log_printf("Release memory\n");
    memoryRelease();
    
    return 0;
}
