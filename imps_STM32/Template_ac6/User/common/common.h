/**
 * @file Common.h
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _COMMON_H
#define _COMMON_H

#include "stm32f10x.h"
#include <stdarg.h>
#include <stdlib.h>

#define macNVIC_PriorityGroup_x NVIC_PriorityGroup_2

/**
 * @brief
 *
 * @param USARTx
 * @param Data
 * @param ...
 */
void USART_printf(USART_TypeDef *USARTx, char *Data, ...);

#endif /* _COMMON_H */