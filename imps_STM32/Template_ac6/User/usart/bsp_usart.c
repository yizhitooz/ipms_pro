/**
 * @file bsp_usart.c
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "bsp_usart.h"

static void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 选择嵌套向量中断控制器组

    // 配置NVIC
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = DEBUG_USART_IRQ; // 配置USART为中断源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;               // 抢断优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;               // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          // 使能中断

    NVIC_Init(&NVIC_InitStructure); // 初始化配置NVIC
}

void USART_Config()
{
    // GPIO
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE); // 打开 GPIO 时钟
    // 配置 TX 和 RX GPIO 的工作模式
    GPIO_InitTypeDef GPIO_InitStruct;
    // TX:推挽复用模式
    GPIO_InitStruct.GPIO_Pin   = DEBUG_USART_TX_GPIO_PIN;  // Pin_9
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;          // 模式:推挽复用
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;         // 速度:50MHZ
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct); // 初始化函数
    // RX:浮空输入模式
    GPIO_InitStruct.GPIO_Pin  = DEBUG_USART_RX_GPIO_PIN;   // Pin_10
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;     // 模式:浮空输入
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct); // 初始化函数

    // 串口外设串口
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE); // 打开串口外设的时钟
    // 外设串口配置
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate            = DEBUG_USART_BAURATE;            // 波特率:115200
    USART_InitStruct.USART_WordLength          = USART_WordLength_8b;            // 帧数据字长
    USART_InitStruct.USART_StopBits            = USART_StopBits_1;               // 停止位
    USART_InitStruct.USART_Parity              = USART_Parity_No;                // 校验位:无
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制:不使用
    USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  // 工作模式:收发一体
    USART_Init(DEBUG_USARTx, &USART_InitStruct);                                 // 初始化函数

    // 串口中断优先级
    NVIC_Configuration();
    // 使能串口接收中断
    USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
    USART_ITConfig(DEBUG_USARTx, USART_IT_IDLE, ENABLE);
    // 使能串口
    USART_Cmd(DEBUG_USARTx, ENABLE);
}

void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t data_8b)
{
    USART_SendData(pUSARTx, data_8b);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void USART_SendStr(USART_TypeDef *pUSARTx, char *str)
{
    char *pStr = str;
    do {
        // 等待发送缓冲区复位
        while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
        USART_SendData(pUSARTx, *pStr);
        pStr += 1;
    } while (*pStr != '\0');
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

int fputc(int ch, FILE *f)
{
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);
    return (ch);
}

int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);
    return (int)USART_ReceiveData(DEBUG_USARTx);
}