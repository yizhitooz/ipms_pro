/**
 * @brief
 *
 */

#include "bsp_esp8266.h"
#include "core_delay.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "bsp_usart.h"

struct STRUCT_USARTx_Fram strEsp8266_Fram_Record = {0};
struct STRUCT_USARTx_Fram strUSART_Fram_Record   = {0};

volatile uint8_t ucTcpClosedFlag = 0;

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

void ESP8266_Rst(void)
{
    macESP8266_RST_LOW_LEVEL();
    Delay_ms(500);
    macESP8266_RST_HIGH_LEVEL();
}

bool ESP8266_Cmd(char *cmd, char *reply1, char *reply2, u32 waittime)
{
    strEsp8266_Fram_Record.InfBit.FramLength = 0; // 从新开始接收新的数据包

    macESP8266_Usart("%s\r\n", cmd);

    if ((reply1 == 0) && (reply2 == 0)) // 不需要接收数据
        return true;

    Delay_ms(waittime); // 延时

    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';

    macPC_Usart("%s", strEsp8266_Fram_Record.Data_RX_BUF);
    strEsp8266_Fram_Record.InfBit.FramLength     = 0; // 清除接收标志
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;

    if ((reply1 != 0) && (reply2 != 0))
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply1) ||
                (bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply2));
    else if (reply1 != 0)
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply1));
    else
        return ((bool)strstr(strEsp8266_Fram_Record.Data_RX_BUF, reply2));
}

bool ESP8266_AT_Test()
{
    char count = 0;

    macESP8266_RST_HIGH_LEVEL();
    printf("\r\nAT测试.....\r\n");
    Delay_ms(2000);
    while (count < 10) {
        printf("\r\nAT测试次数 %d......\r\n", count);
        if (ESP8266_Cmd("AT", "OK", NULL, 500)) {
            printf("\r\nAT测试启动成功 %d......\r\n", count);
            return 1;
        }
        ESP8266_Rst();
        count++;
    }
    return 0;
}

bool ESP8266_Net_Mode_Choose(ENUM_Net_ModeTypeDef enumMode)
{
    switch (enumMode) {
        case STA:
            return ESP8266_Cmd("AT+CWMODE=1", "OK", "no change", 2500);
        case AP:
            return ESP8266_Cmd("AT+CWMODE=2", "OK", "no change", 2500);
        case STA_AP:
            return ESP8266_Cmd("AT+CWMODE=3", "OK", "no change", 2500);
        default:
            return false;
    }
}

bool ESP8266_JoinAP(char *pSSID, char *pPassWord)
{
    char cCmd[120];

    sprintf(cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord);

    return ESP8266_Cmd(cCmd, "OK", NULL, 5000);
}

bool ESP8266_DHCP_CUR()
{
    char cCmd[40];

    sprintf(cCmd, "AT+CWDHCP_CUR=1,1");

    return ESP8266_Cmd(cCmd, "OK", NULL, 500);
}

bool ESP8266_Enable_MultipleId(FunctionalState enumEnUnvarnishTx)
{
    char cStr[20];

    sprintf(cStr, "AT+CIPMUX=%d", (enumEnUnvarnishTx ? 1 : 0));

    return ESP8266_Cmd(cStr, "OK", 0, 500);
}

bool ESP8266_Link_Server(ENUM_NetPro_TypeDef enumE, char *ip,
                         char *ComNum, ENUM_ID_NO_TypeDef id)
{
    char cStr[100] = {0}, cCmd[120];

    switch (enumE) {
        case enumTCP:
            sprintf(cStr, "\"%s\",\"%s\",%s", "TCP", ip, ComNum);
            break;

        case enumUDP:
            sprintf(cStr, "\"%s\",\"%s\",%s", "UDP", ip, ComNum);
            break;

        default:
            break;
    }

    if (id < 5)
        sprintf(cCmd, "AT+CIPSTART=%d,%s", id, cStr);

    else
        sprintf(cCmd, "AT+CIPSTART=%s", cStr);

    return ESP8266_Cmd(cCmd, "OK", "ALREAY CONNECT", 4000);
}

bool ESP8266_UnvarnishSend()
{
    if (!ESP8266_Cmd("AT+CIPMODE=1", "OK", 0, 500))
        return false;

    return ESP8266_Cmd("AT+CIPSEND", "OK", ">", 500);
}

void ESP8266_ExitUnvarnishSend()
{
    Delay_ms(1000);

    macESP8266_Usart("+++");

    Delay_ms(500);
}

bool ESP8266_SendString(FunctionalState enumEnUnvarnishTx, char *pStr,
                        u32 ulStrLength, ENUM_ID_NO_TypeDef ucId)
{
    bool bRet = false;
    if (enumEnUnvarnishTx) {
        macESP8266_Usart("%s", pStr);
        bRet = true;
    } else {
        char cStr[20];
        if (ucId < 5)
            sprintf(cStr, "AT+CIPSEND=%d,%d", ucId, ulStrLength + 2);

        else
            sprintf(cStr, "AT+CIPSEND=%d", ulStrLength + 2);

        ESP8266_Cmd(cStr, "> ", 0, 100);
        bRet = ESP8266_Cmd(pStr, "SEND OK", 0, 500);
    }

    return bRet;
}

char *ESP8266_ReceiveString(FunctionalState enumEnUnvarnishTx)
{
    char *pRecStr = 0;

    strEsp8266_Fram_Record.InfBit.FramLength     = 0;
    strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;

    while (!strEsp8266_Fram_Record.InfBit.FramFinishFlag);
    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';

    if (enumEnUnvarnishTx)
        pRecStr = strEsp8266_Fram_Record.Data_RX_BUF;

    else {
        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+IPD"))
            pRecStr = strEsp8266_Fram_Record.Data_RX_BUF;
    }

    return pRecStr;
}

uint8_t ESP8266_Get_LinkStatus()
{
    if (ESP8266_Cmd("AT+CIPSTATUS", "OK", 0, 500)) {
        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "STATUS:2\r\n"))
            return 2;

        else if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "STATUS:3\r\n"))
            return 3;

        else if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "STATUS:4\r\n"))
            return 4;
    }

    return 0;
}

uint8_t ESP8266_Get_IdLinkStatus()
{
    uint8_t ucIdLinkStatus = 0x00;

    if (ESP8266_Cmd("AT+CIPSTATUS", "OK", 0, 500)) {
        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+CIPSTATUS:0,"))
            ucIdLinkStatus |= 0x01;
        else
            ucIdLinkStatus &= ~0x01;

        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+CIPSTATUS:1,"))
            ucIdLinkStatus |= 0x02;
        else
            ucIdLinkStatus &= ~0x02;

        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+CIPSTATUS:2,"))
            ucIdLinkStatus |= 0x04;
        else
            ucIdLinkStatus &= ~0x04;

        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+CIPSTATUS:3,"))
            ucIdLinkStatus |= 0x08;
        else
            ucIdLinkStatus &= ~0x08;

        if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "+CIPSTATUS:4,"))
            ucIdLinkStatus |= 0x10;
        else
            ucIdLinkStatus &= ~0x10;
    }

    return ucIdLinkStatus;
}

void ESP8266_StaTcpClient_Unvarnish_ConfigTest()
{
    printf("\r\n正在配置 ESP8266 ......\r\n");
    printf("\r\n使能 ESP8266 ......\r\n");
    macESP8266_CH_ENABLE();
    while (!ESP8266_AT_Test());
    printf("\r\n开启DHCP ......\r\n");
    while (!ESP8266_DHCP_CUR());
    printf("\r\n正在配置工作模式 STA ......\r\n");
    while (!ESP8266_Net_Mode_Choose(STA));

    printf("\r\n正在连接 WiFi ......\r\n");
    while (!ESP8266_JoinAP(macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd));

    printf("\r\n禁止多连接 ......\r\n");
    while (!ESP8266_Enable_MultipleId(DISABLE));
    printf("\r\n正在连接 Server ......\r\n");
    uint8_t flag = 0;
    while (!ESP8266_Link_Server(enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0));
    printf("\r\n进入透传发送模式 ......\r\n");
    while (!ESP8266_UnvarnishSend());

    printf("\r\n配置 ESP8266 完毕\r\n");
    printf("\r\n开始透传......\r\n");
}

void ESP8266_CheckRecvDataTest(void)
{
    uint8_t ucStatus;
    uint16_t i;

    /* 如果接收到了串口调试助手的数据 */
    if (strUSART_Fram_Record.InfBit.FramFinishFlag == 1) {
        for (i = 0; i < strUSART_Fram_Record.InfBit.FramLength; i++) {
            USART_SendData(macESP8266_USARTx, strUSART_Fram_Record.Data_RX_BUF[i]); // 转发给ESP82636
            while (USART_GetFlagStatus(macESP8266_USARTx, USART_FLAG_TC) == RESET) {
            } // 等待发送完成
        }
        strUSART_Fram_Record.InfBit.FramLength     = 0; // 接收数据长度置零
        strUSART_Fram_Record.InfBit.FramFinishFlag = 0; // 接收标志置零
    }

    /* 如果接收到了ESP8266的数据 */
    if (strEsp8266_Fram_Record.InfBit.FramFinishFlag) {
        for (i = 0; i < strEsp8266_Fram_Record.InfBit.FramLength; i++) {
            USART_SendData(DEBUG_USARTx, strEsp8266_Fram_Record.Data_RX_BUF[i]); // 转发给 ESP8266
            while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TC) == RESET);
        }
        strEsp8266_Fram_Record.InfBit.FramLength     = 0; // 接收数据长度置零
        strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0; // 接收标志置零
    }

    if (ucTcpClosedFlag) // 检测是否失去连接
    {
        ESP8266_ExitUnvarnishSend(); // 退出透传模式

        do
            ucStatus = ESP8266_Get_LinkStatus(); // 获取连接状态
        while (!ucStatus);

        if (ucStatus == 4) // 确认失去连接后重连
        {
            printf("\r\n正在重连热点和服务器 ......\r\n");

            while (!ESP8266_JoinAP(macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd));
            while (!ESP8266_Link_Server(enumTCP, macUser_ESP8266_TcpServer_IP,
                                        macUser_ESP8266_TcpServer_Port, Single_ID_0));
            printf("\r\n重连热点和服务器成功\r\n");
        }

        while (!ESP8266_UnvarnishSend());
    }
}