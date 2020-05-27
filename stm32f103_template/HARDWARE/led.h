#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define LED_R_ON    (GPIO_ResetBits(GPIOB,GPIO_Pin_5))
#define LED_R_OFF   (GPIO_SetBits(GPIOB, GPIO_Pin_5))
#define LED_G_ON    (GPIO_ResetBits(GPIOE,GPIO_Pin_5))
#define LED_G_OFF   (GPIO_SetBits(GPIOE, GPIO_Pin_5))

extern void led_init(void);
#endif
