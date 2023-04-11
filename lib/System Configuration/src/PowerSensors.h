#include "Main.h"

#if MCU_CHOICE == 0
#include "STM32F103C8T6PowerSensors.h"
#elif MCU_CHOICE == 1

#else
#error "Select the correct Memory Map!"
#endif