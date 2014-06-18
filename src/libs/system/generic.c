#include "generic.h"
#include <stm32f4xx.h>

uint __critical_enter(void)
{
    uint mask = __get_PRIMASK();
    __disable_irq();
    return mask;
}

void __critical_exit(uint mask)
{
    __set_PRIMASK(mask);
}

uint __atomic_enter(void)
{
    uint mask = __get_BASEPRI();
    __set_BASEPRI(96);
    return mask;
}

void __atomic_exit(uint mask)
{
    __set_BASEPRI(mask);
}

