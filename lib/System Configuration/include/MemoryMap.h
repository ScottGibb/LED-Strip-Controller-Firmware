#include "Main.h"

#if MCU_CHOICE == 0
#include "Server Rack Controller/MemoryMap.h"
#elif MCU_CHOICE == 1

#else
#error "Select the correct Memory Map!"
#endif