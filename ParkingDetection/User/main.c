#include "stm32f10x.h"

int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_ITD_Struct;

    GPIO_ITD_Struct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_ITD_Struct.GPIO_Pin   = GPIO_Pin_5;
    GPIO_ITD_Struct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_ITD_Struct);
}