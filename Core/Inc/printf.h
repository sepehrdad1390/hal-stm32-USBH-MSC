
#ifndef _PRINTF_H
#define _PRINTF_H

#include "stdio.h"
#include "main.h"

//#define USB_CDC
#define USART

#ifdef USART
#define printf_uart huart1
extern UART_HandleTypeDef printf_uart;
#endif

#ifdef USB_CDC
#include "usb_device.h"
#endif

#ifdef USART
#if defined(__GNUC__)
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&printf_uart,(uint8_t *)&ch,1,HAL_MAX_DELAY);
  return ch;
}
#elif defined (__CC_ARM)
int fputc(int ch, FILE *f)
{
	  HAL_UART_Transmit(&printf_uart,(uint8_t *)&ch,1,HAL_MAX_DELAY);
  return ch;
}
#elif defined (__ICCARM__)
size_t __write(int handle,const unsigned char *buffer,size_t size)
{
  HAL_UART_Transmit(&printf_uart,(uint8_t *)buffer,size,HAL_MAX_DELAY);
  return size;
}
#endif
#elif defined USB_CDC
#if defined(__GNUC__)
int __io_putchar(int ch)
{
    CDC_Transmit_FS((uint8_t *)&ch,1);
  return ch;
}
#elif defined (__CC_ARM)
int fputc(int ch, FILE *f)
{
  CDC_Transmit_FS((uint8_t *)&ch,1);
  return ch;
}
#elif defined (__ICCARM__)
size_t __write(int handle,const unsigned char *buffer,size_t size)
{
  CDC_Transmit_FS((uint8_t *)buffer,size);
  return size;
}
#endif
#endif



#endif
