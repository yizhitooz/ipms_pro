/**
 * @file bsp_8266.h
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _BSP_ESP_8266
#define _BSP_ESP_8266
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "stdbool.h"
#include <string.h>

#if defined(__CC_ARM)
#pragma anon_unions
#endif

typedef enum {
    STA,
    AP,
    STA_AP
} ENUM_Net_ModeTypeDef; // 工作模式

typedef enum {
    enumTCP,
    enumUDP,
} ENUM_NetPro_TypeDef;

typedef enum {
    Multiple_ID_0 = 0,
    Multiple_ID_1 = 1,
    Multiple_ID_2 = 2,
    Multiple_ID_3 = 3,
    Multiple_ID_4 = 4,
    Single_ID_0   = 5,
} ENUM_ID_NO_TypeDef;

typedef enum {
    OPEN         = 0,
    WEP          = 1,
    WPA_PSK      = 2,
    WPA2_PSK     = 3,
    WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef; // 密码类型

#define RX_BUF_MAX_LEN 1024

extern struct STRUCT_USARTx_Fram {
    char Data_RX_BUF[RX_BUF_MAX_LEN];

    union {
        __IO u16 InfAll;
        struct
        {
            __IO u16 FramLength : 15;    // 14:0
            __IO u16 FramFinishFlag : 1; // 15
        } InfBit;
    };

} strEsp8266_Fram_Record;

extern struct STRUCT_USARTx_Fram strUSART_Fram_Record;

// USART 相关配置
#define macESP8266_CH_PD_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define macESP8266_CH_PD_CLK                RCC_APB2Periph_GPIOG
#define macESP8266_CH_PD_PORT               GPIOG
#define macESP8266_CH_PD_PIN                GPIO_Pin_13

#define macESP8266_RST_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define macESP8266_RST_CLK                  RCC_APB2Periph_GPIOG
#define macESP8266_RST_PORT                 GPIOG
#define macESP8266_RST_PIN                  GPIO_Pin_14

#define macESP8266_USART_BAUD_RATE          115200

#define macESP8266_USARTx                   USART3
#define macESP8266_USART_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define macESP8266_USART_CLK                RCC_APB1Periph_USART3
#define macESP8266_USART_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define macESP8266_USART_GPIO_CLK           RCC_APB2Periph_GPIOB
#define macESP8266_USART_TX_PORT            GPIOB
#define macESP8266_USART_TX_PIN             GPIO_Pin_10
#define macESP8266_USART_RX_PORT            GPIOB
#define macESP8266_USART_RX_PIN             GPIO_Pin_11
#define macESP8266_USART_IRQ                USART3_IRQn
#define macESP8266_USART_INT_FUN            USART3_IRQHandler

// WiFi 相关配置

#define macUser_ESP8266_ApSsid         "GUET-WiFi" // 要连接的热点的名称
#define macUser_ESP8266_ApPwd          ""          // 要连接的热点的密钥

#define macUser_ESP8266_TcpServer_IP   "10.38.169.36" // 要连接的服务器的 IP
#define macUser_ESP8266_TcpServer_Port "8000"         // 要连接的服务器的端口

// 外部全局变量
extern volatile uint8_t ucTcpClosedFlag;

#define macESP8266_Usart(fmt, ...) \
    USART_printf(macESP8266_USARTx, fmt, ##__VA_ARGS__)
// 向计算机的 USB 串口发送字符串
#define macPC_Usart(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define macESP8266_CH_ENABLE() \
    GPIO_SetBits(macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN)
#define macESP8266_CH_DISABLE() \
    GPIO_ResetBits(macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN)

#define macESP8266_RST_HIGH_LEVEL() \
    GPIO_SetBits(macESP8266_RST_PORT, macESP8266_RST_PIN)
#define macESP8266_RST_LOW_LEVEL() \
    GPIO_ResetBits(macESP8266_RST_PORT, macESP8266_RST_PIN)

/**
 * @brief
 * 初始化
 */
void ESP8266_Init();

/**
 * @brief
 * 重置
 */
void ESP8266_Rst();

#endif /* _BSP_ESP_8266 */