/*!-----------------------------------------------------------------------------
*
* @file		my_usart.h
* @brief	串口头文件
* @author	S.T.A.R.
* @version	0.1
* @date		Wed 22 Apr 2020 12:46:29 PM CST
*
*-----------------------------------------------------------------------------*/

/*----------------------------- 头文件包含 -----------------------------------*/
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include <stdio.h>
/*------------------------------- 宏定义 -------------------------------------*/

/*----------------------------- 函数声明 -------------------------------------*/
void usart_send_byte(uint16_t data);
void usart_send_string(USART_TypeDef * pUSARTx, char *str);
void usart_rev_byte(u8 *data);
void usart_init();

extern u8 usart_RcvData;
