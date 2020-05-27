/*!-----------------------------------------------------------------------------
*
* @file		my_usart.c
* @brief	串口驱动
* @author	S.T.A.R.
* @version	0.2
* @date		Wed 22 Apr 2020 11:01:06 AM CST
*
* @version	0.2
* @date     Tue 19 May 2020 09:44:19 PM CST
* 重定向_write函数,可使用格式化输出
*-----------------------------------------------------------------------------*/

/*----------------------------- 头文件包含 -----------------------------------*/
#include "my_usart.h"
#include <stdio.h>
#include <stdlib.h>
/*------------------------------- 宏定义 -------------------------------------*/
u8 usart_RcvData = 0;
/*----------------------------- 接口函数 -------------------------------------*/
/*!-----------------------------------------------------------------------------
* @brief	串口初始化
* @param	None
* @retval	None
* @version 0.1
*----------------------------------------------------------------------------*/
void usart_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* 时钟使能 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* USART1_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 串口配置 */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = \
                                            USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* usart1 使能 */
    USART_Cmd(USART1, ENABLE);
}
/*!-----------------------------------------------------------------------------
* @brief	串口发送
* @param	data 发送的数据
* @retval	None
* @version 0.1
*----------------------------------------------------------------------------*/
void usart_send_byte(uint16_t data)
{
    USART_SendData(USART1, data);
    while(RESET == USART_GetFlagStatus(USART1,USART_FLAG_TXE))
    {

    }
}
/*!-----------------------------------------------------------------------------
* @brief	发送字符串
* @param	str 发送的字符串
* @retval	None
* @version 0.1
*----------------------------------------------------------------------------*/
void usart_send_string(USART_TypeDef *pUSARTx, char *str)
{

    do
    {
        usart_send_byte(*str);
        str++;
    }
    while(*str  != '\0');

    while(RESET == USART_GetFlagStatus(pUSARTx, USART_FLAG_TC))
    {

    }
}
/*!-----------------------------------------------------------------------------
* @brief	串口接收
* @param	data 接收到的数据
* @retval	None
* @version 0.1
*----------------------------------------------------------------------------*/
void usart_rev_byte(u8 *data)
{
    while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
    {

    }
    *data = USART_ReceiveData(USART1);
}
/*!-----------------------------------------------------------------------------
* @brief	重定向函数
* @param	
* @retval	
* @version 0.1
*----------------------------------------------------------------------------*/
int _write(int fd, char *ptr, int len)
{
    int i = 0;

    if(fd > 2)
    {
        return -1;
    }

    while(*ptr && (i < len))
    {
        usart_send_byte(*ptr);

        if(*ptr == '\n')
        {
            usart_send_byte('\r');
        }
        i++;
        ptr++;
    }

    return i;
}
/*!-----------------------------------------------------------------------------
* @brief	USART终端服务函数
* @param	None
* @retval	None
* @version 0.1
*----------------------------------------------------------------------------*/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        usart_RcvData = USART_ReceiveData(USART1);
        /* USART_SendData(USART1, usart_RcvData); */
    }
}
