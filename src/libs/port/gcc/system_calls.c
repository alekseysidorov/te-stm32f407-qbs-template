#include <generic.h>
#include <stm32f4xx.h>

uint sys_now(void)
{
    return system_time() * 1000;
}
