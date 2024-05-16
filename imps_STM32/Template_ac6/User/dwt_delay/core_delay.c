#include "./dwt_delay/core_delay.h"
#include "core_delay.h"

#if _USE_DWT_DELAY

#define DWT_CR           *(__IO uint32_t *)0xE0001000
#define DWT_CYCCNT       *(__IO uint32_t *)0xE0001004
#define DEM_CR           *(__IO uint32_t *)0xE000EDFC

#define DEM_CR_TRCENA    (1 << 24)
#define DWT_CR_CYCCNTENA (1 << 0)

void CPU_TS_TmrInit()
{
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;
    DWT_CYCCNT = (uint32_t)0u;
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

uint32_t CPU_TS_TmrRd()
{
    return ((uint32_t)DWT_CYCCNT);
}

void CPU_TS_Tmr_Delay_US(__IO uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;

#if (CPU_TS_INIT_IN_DELAY_FUNCTION)
    CPU_TS_TmrInit();
#endif

    ticks = us * (GET_CPU_ClkFreq() / 1000000);
    tcnt  = 0;
    told  = (uint32_t)CPU_TS_TmrRd();

    while (1) {
        tnow = (uint32_t)CPU_TS_TmrRd();
        if (tnow != told) {
            if (tnow > told) {
                tcnt += tnow - told;
            } else {
                tcnt += UINT32_MAX - told + tnow;
            }
            told = tnow;
            if (tcnt >= ticks)
                break;
        }
    }
}
#endif