/**
 * @file main.c
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "bsp_gpio.h"
#include "bsp_usart.h"
#include "bsp_esp8266.h"
#include "core_delay.h"
#include <stdio.h>
#include "stm32f10x_iwdg.h"

void Watchdog_Init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload(60000);
    IWDG_ReloadCounter();
    IWDG_Enable();
}

void Watchdog_Refresh(void)
{
    IWDG_ReloadCounter();
}

int main()
{
    CPU_TS_TmrInit(); // 初始化 DWT 计数器
    USART_Config();   // 初始化 USART 串口
    ESP8266_Init();   // 初始化 WiFi 模块使用的接口和外设

    macESP8266_CH_ENABLE(); // 使能 ESP8266

    Watchdog_Init(); // 初始化看门狗

    ESP8266_StaTcpClient_Unvarnish_ConfigTest();
    while (1) {
        float distance =
            getDistance_SoundSpeed_m(
                DistanceSensor_Tri_Port,
                DistanceSensor_Tri_Pin,
                DistanceSensor_Echo_Port,
                DistanceSensor_Tri_Pin);

        if (distance > 3) {
            printf("车位空闲");
        } else {
            printf("车位占用");
        }
        Watchdog_Refresh();
        Delay_s(30);
    }
}