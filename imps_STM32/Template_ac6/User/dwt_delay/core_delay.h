#ifndef __CORE_DELAY_H
#define __CORE_DELAY_H

#include "stm32f10x.h"

#define _USE_DWT_DELAY 1 /* 使用 DWT 内核精确延时 */

#if _USE_DWT_DELAY
#define _USE_TICK_DELAY 0 /* 不使用 SysTick 延时 */
#else
#define _USE_TICK_DELAY 1 /* 使用 SysTick 延时 */
#endif

#define TASK_ENABLE 0
#define NumOfTask   3

#if _USE_DWT_DELAY

#define Delay_ms(ms)                  CPU_TS_Tmr_Delay_MS(ms)
#define Delay_us(us)                  CPU_TS_Tmr_Delay_US(us)

#define Delay_s(s)                    CPU_TS_Tmr_Delay_S(s)

#define GET_CPU_ClkFreq()             (SystemCoreClock)
#define SysClockFreq                  (SystemCoreClock)

#define CPU_TS_INIT_IN_DELAY_FUNCTION 0

/**
 * @brief
 *
 * @return uint32_t
 */
uint32_t CPU_TS_TmrRd();

/**
 * @brief
 *
 */
void CPU_TS_TmrInit();

/**
 * @brief
 *
 * @param us
 */
void CPU_TS_Tmr_Delay_US(__IO uint32_t us);

#define CPU_TS_Tmr_Delay_MS(ms) CPU_TS_Tmr_Delay_US(ms * 1000)
#define CPU_TS_Tmr_Delay_S(s)   CPU_TS_Tmr_Delay_MS(s * 1000)

#endif

#endif /* _CORE_DELAY_H */