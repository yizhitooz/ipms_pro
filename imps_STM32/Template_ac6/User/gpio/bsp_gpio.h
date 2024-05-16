/**
 * @file bsp_gpio.h
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define RCC_DistanceSensor_Tri   RCC_APB2Periph_GPIOA
#define DistanceSensor_Tri_Port  GPIOA
#define DistanceSensor_Tri_Pin   GPIO_Pin_13
#define RCC_DistanceSensor_echo  RCC_APB2Periph_GPIOA
#define DistanceSensor_Echo_Port GPIOA
#define DistanceSensor_Echo_Pin  GPIO_Pin_12

#define SPEED_OF_SOUND           340.0

/**
 * @brief
 *
 */
void GPIO_Config();

/**
 * @brief Get the Distance SoundSpeed m object
 *
 * @param GPIO_Tri_x
 * @param Pin_tri_x
 * @param GPIO_Echo_x
 * @param Pin_Echo_x
 * @return float
 */
float getDistance_SoundSpeed_m(GPIO_TypeDef *GPIO_Tri_x, uint16_t Pin_tri_x,
                               GPIO_TypeDef *GPIO_Echo_x, uint16_t Pin_Echo_x);

#endif /* _BSP_GPIO_H */