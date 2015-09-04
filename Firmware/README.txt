When building the bootloader, the Cpu_Init.c file will be overwritten with the default when Processor Expert files are generated, which will stop the bootloader from operating.

This file must be modified manually after each Processor Expert build as follows:

add this line at the top with the other includes:
#include "bootloader.h"

add this line near the top of the function PEX_ENTRYPOINT_FUNCTION_TYPE PEX_ENTRYPOINT_FUNCTION(), just after the first #if block:
BL_CheckForuserApp();

Then build the project again and the bootloader will work.