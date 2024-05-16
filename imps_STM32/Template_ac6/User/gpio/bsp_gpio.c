/**
 * @file bsp_gpio.c
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "bsp_gpio.h"
#include "stm32f10x_gpio.h"
#include "./dwt_delay/core_delay.h"

void GPIO_Config()
{
    RCC_APB2PeriphClockCmd(RCC_DistanceSensor_Tri, ENABLE);
    // 距离传感器
    GPIO_InitTypeDef gpio_ITD_Struct;
    gpio_ITD_Struct.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpio_ITD_Struct.GPIO_Pin   = DistanceSensor_Tri_Pin;
    gpio_ITD_Struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DistanceSensor_Tri_Port, &gpio_ITD_Struct);

    gpio_ITD_Struct.GPIO_Mode = GPIO_Mode_IPD;
    gpio_ITD_Struct.GPIO_Pin  = DistanceSensor_Echo_Pin;
    GPIO_Init(DistanceSensor_Echo_Port, &gpio_ITD_Struct);

    GPIO_ResetBits(DistanceSensor_Tri_Port, DistanceSensor_Tri_Pin);
}

float getDistance_SoundSpeed_m(GPIO_TypeDef *GPIO_Tri_x, uint16_t Pin_tri_x,
                               GPIO_TypeDef *GPIO_Echo_x, uint16_t Pin_Echo_x)
{
    GPIO_SetBits(GPIO_Tri_x, Pin_tri_x);
    Delay_us(10);
    GPIO_ResetBits(GPIO_Tri_x, Pin_tri_x);

    while (!GPIO_ReadInputDataBit(GPIO_Echo_x, Pin_Echo_x));
    uint32_t start = CPU_TS_TmrRd();         // DWT 时间
    uint32_t time  = CPU_TS_TmrRd() - start; // 当前经过的 DWT 时间

    while (GPIO_ReadInputDataBit(GPIO_Echo_x, Pin_Echo_x))
        if (time > 1000000000) // 防止传感器接收不到回响不断计时
            break;
    const float GAP_DISTANCE =
        time / 100000000.0 * SPEED_OF_SOUND / 2.0;
    return GAP_DISTANCE;
}