/**
 * @file bsp_usart.h
 * @author UZALWONG (uzalwong@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>

// USART1
#define DEBUG_USARTx USART1
#define DEBUG_USART_CLK RCC_APB2Periph_USART1 // APB2->USART1
#define DEBUG_USART_APBxClkCmd RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAURATE 115200

// USART_GPIO_PIN
#define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOA)
#define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT GPIOA
#define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_9
#define DEBUG_USART_RX_GPIO_PORT GPIOA
#define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_10

#define DEBUG_USART_IRQ USART1_IRQn
#define DEBUG_USART_IRQHandler USART1_IRQHandler

static void NVIC_Configuration(void);

/**
 * @brief 初始化 USART
 *
 */
void USART_Config();

/**
 * @brief 向串口发送一个 8 位数据(字符)
 *
 * @param pUSARTx 串口指针
 * @param date_8b 8位数据(字符)
 */
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t data_8b);

/**
 * @brief 向串口发送一串字符
 *
 * @param pUSARTx 串口指针
 * @param str 字符串指针
 */
void USART_SendStr(USART_TypeDef *pUSARTx, char *str);

/**
 * @brief 发送数据到串口
 * @note 重定向 C 库函数,来使用 printf 函数往串口发送数据
 *
 * @param ch
 * @param f
 * @return int
 */
int fputc(int ch, FILE *f);

/**
 * @brief 接收来自串口的数据
 * @note 重定向 C 库函数,来使用 scanf、getchar 接收来自串口的数据
 *
 * @param f
 * @return int
 */
int fgetc(FILE *f);

#endif /* _BSP_USART_H */