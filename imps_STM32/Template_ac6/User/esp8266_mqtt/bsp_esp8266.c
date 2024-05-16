/**
 * @brief
 *
 */

#include "bsp_esp8266.h"
#include "common.h"

/**
 * @brief
 * 配置 ESP8266模块的 USART
 */
static void ESP8266_USART_Config();

/**
 * @brief
 * 配置ESP8266 USART 的 NVIC 中断
 */
static void ESP8266_USART_NVIC_Configuration();

/**
 * @brief
 * 配置 ESP8266 模块的 GPIO
 */
static void ESP8266_GPIO_Config();

void ESP8266_Init()
{
    ESP8266_GPIO_Config();
    ESP8266_USART_Config();

    macESP8266_RST_HIGH_LEVEL();
    macESP8266_CH_DISABLE();
}

static void ESP8266_GPIO_Config()
{
    // CH_PD
    // 开时钟
    macESP8266_CH_PD_APBxClock_FUN(macESP8266_CH_PD_CLK, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    // 设置引脚为推挽输出模式
    GPIO_InitStruct.GPIO_Pin   = macESP8266_CH_PD_PIN;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(macESP8266_CH_PD_PORT, &GPIO_InitStruct);

    // RST
    // 开时钟
    macESP8266_RST_APBxClock_FUN(macESP8266_RST_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = macESP8266_RST_PIN;

    GPIO_Init(macESP8266_RST_PORT, &GPIO_InitStruct);
}

static void ESP8266_USART_Config()
{
    // STM32 <-> USART <-> ESP8266
    // USART.GPIO 配置
    macESP8266_USART_GPIO_APBxClock_FUN(macESP8266_USART_GPIO_CLK, ENABLE); // 开时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    // TX
    // 配置GPIO为浮空输入模式
    GPIO_InitStructure.GPIO_Pin  = macESP8266_USART_RX_PIN;   // GPIOB->PIN11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;     // 浮空输入
    GPIO_Init(macESP8266_USART_RX_PORT, &GPIO_InitStructure); // 初始化 ESP8266 的 RX 引脚

    // RX
    // 配置GPIO为复用功能推挽输出模式
    GPIO_InitStructure.GPIO_Pin   = macESP8266_USART_TX_PIN;  // GPIOB->PIN10
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;          // 复用功能推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 50MHZ
    GPIO_Init(macESP8266_USART_TX_PORT, &GPIO_InitStructure); // 初始化 ESP8266 的 TX 引脚

    // USART 配置
    macESP8266_USART_APBxClock_FUN(macESP8266_USART_CLK, ENABLE); // 开时钟

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = macESP8266_USART_BAUD_RATE;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(macESP8266_USARTx, &USART_InitStructure);

    USART_ITConfig(macESP8266_USARTx, USART_IT_RXNE, ENABLE); // 使能串口接收中断
    USART_ITConfig(macESP8266_USARTx, USART_IT_IDLE, ENABLE); // 使能串口总线空闲中断

    ESP8266_USART_NVIC_Configuration();

    USART_Cmd(macESP8266_USARTx, ENABLE);
}

static void ESP8266_USART_NVIC_Configuration()
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(macNVIC_PriorityGroup_x);

    // 使能USART2 中断
    NVIC_InitStructure.NVIC_IRQChannel                   = macESP8266_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
