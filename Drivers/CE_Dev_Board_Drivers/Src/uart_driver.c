/**
 * @file: uart_driver.c
 * @author: Grant Wilk
 * @modified: 2/4/2020
 * @description: a UART driver for the MCU's USART2 module
*/

# include <stdio.h>
# include "uart_driver.h"
# include "circular_queue.h"
# include "stm32f446xx.h"

/**
 * Stores characters after they are read from the RDR
 */
static circular_queue input_buffer;


/**
 * Stores characters until they are transmitted by the TDR
 */
static circular_queue output_buffer;

/**
 * Initializes USART2 as a UART
 * @param baud - the baud rate
 * @param sysclk - the frequency of the system clock in Hz
 */
void uart_init(int baud, int sysclk) {

    // define the input and output buffer
    input_buffer = cq_init();
    output_buffer = cq_init();

    // enable GPIOA in RCC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // enable USART2 in RCC
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // set PA2 and PA3 as pullup
    GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD2_Pos | 0b01 << GPIO_PUPDR_PUPD3_Pos);

    // clear PA2 and PA3 mode
    GPIOA->MODER &= ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3);

    // set PA2 and PA3 mode to alternate function
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODER2_Pos | 0b10 << GPIO_MODER_MODER3_Pos);

    // clear alternate function select for PA2 and PA3
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);

    // select USART1..3 (AF7) as the alternate function for PA3 and PA2
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos | 7 << GPIO_AFRL_AFSEL3_Pos);

    // set USART2's baud rate
    USART2->BRR = sysclk / baud;

    // enable USART2's UART, RX, and TX
    USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

    // enable USART2's TXE interrupt and RXNE interrupt
    USART2->CR1 |= (USART_CR1_TXEIE | USART_CR1_RXNEIE);

    // enable USART2 interrupts in NVIC
    NVIC->ISER[1] |= (1 << 6);

    // set output buffer source
    setvbuf(stdout, NULL, _IONBF, 0);

}

/**
 * Reads a string from the UART's input buffer
 * @param file - not implemented (ignored)
 * @param ptr - where the read data should be put
 * @param len - the number of characters to read
 * @return the number of characters read
 */
int _read(int file, char * ptr, int len) {

    // wait until the input buffer receives some data
    while (cq_isempty(&input_buffer));

    int char_count = 0;

    // pull from the circular queue until it is empty
    while (!cq_isempty(&input_buffer)) {
        char_count++;
        *ptr = cq_pull(&input_buffer);
        ptr++;
    }

    if (*ptr == '\r') *ptr = '\n';

    return char_count;

}

/**
 * Writes a string to the UART's output buffer
 * @param file - not implemented (ignored)
 * @param ptr - where the characters should be read from
 * @param len - the number of characters to read
 * @return the number of characters read
 */
int _write(int file, char * ptr, int len) {

    int char_count = 0;

    // push characters to the output buffer until we write len characters or the buffer fills up
    while (char_count < len && !cq_isfull(&output_buffer)) {
        cq_push(&output_buffer, *ptr);
        char_count++;
        ptr++;
    }

    // enable TXE interrupts so the data can be transmitted
    USART2->CR1 |= USART_CR1_TXEIE;

    return char_count;
}

/**
 * USART2 interrupt request handler
 */
void USART2_IRQHandler(void) {

    // if the RDR has received data and the input buffer is not full
    if ((USART2->SR & USART_SR_RXNE) && !cq_isfull(&input_buffer)) {

        // read the RDR
        char c = USART2->DR;

        // push the char in the RDR into the input buffer
        cq_push(&input_buffer, c);

        // echo the character to the output buffer
        if (!cq_isfull(&output_buffer)) {
            cq_push(&output_buffer, c);
        }

        // enable TXE interrupts so the echo can be pushed
        USART2->CR1 |= USART_CR1_TXEIE;

    }

    // if the TDR has completed transmission
    else if (USART2->SR & USART_SR_TXE) {

        // if the output buffer is not empty
        if (!cq_isempty(&output_buffer)) {

            // pull a char out of the output buffer and move it into the TDR
            USART2->DR = cq_pull(&output_buffer);

        } else {

            // disable TXE interrupts
            USART2->CR1 &= ~(USART_CR1_TXEIE);

        }
    }
}
