#ifndef _GENERIC_H_
#define _GENERIC_H_
#include <stdint.h>
#include <stdbool.h>

typedef unsigned int uint;

extern uint __critical_enter(void);
extern void __critical_exit(uint);

extern uint __atomic_enter(void);
extern void __atomic_exit(uint);

extern uint system_time(void);

#define ATOMIC(_code_) \
    { \
        volatile uint __atomic_state = __atomic_enter(); \
        { _code_ } \
        __atomic_exit(__atomic_state); \
    }

#define CRITICAL(_code_) \
    { \
        volatile uint __critical_state = __critical_enter(); \
        { _code_ } \
        __critical_exit(__critical_state); \
    }


static inline bool time_expired(uint *time, uint timeout)
{
    uint currentTime = system_time();
    
    if ((currentTime - *time) < timeout)
        return false;
    
    *time = currentTime;
    return true;
}



#endif // _GENERIC_H_
