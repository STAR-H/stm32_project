#include "led.h"

void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //使能GPIOB和GPIOE时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | \
                           RCC_APB2Periph_GPIOE, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);

    return;
}
