/**
 * @file: uart_driver.h
 * @author: Grant Wilk
 * @modified: 2/4/2020
 * @description: a UART driver for the MCU's USART2 module
*/

/**
 * Initializes USART2 as a UART
 * @param baud - the baud rate
 * @param sysclk - the frequency of the system clock in Hz
 */
void uart_init(int baud, int sysclk);