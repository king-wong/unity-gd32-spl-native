#include "unity_config.h"
#include "gd32f3x0.h"
#include <stdio.h>

/* settings for USART0 alternate settings, TX = PB6, RX = PB7 */
#define RCU_GPIO RCU_GPIOB
#define RCU_UART RCU_USART0
#define USART USART0
#define UART_TX_RX_GPIO GPIOB
#define UART_TX_GPIO_PIN GPIO_PIN_6
#define UART_RX_GPIO_PIN GPIO_PIN_7

#define USART0_RDATA_ADDRESS ((uint32_t)0x40013824)
#define USART0_TDATA_ADDRESS ((uint32_t)0x40013828)

#define BAUD_RATE 115200U


/* for printf() via semihosting */
#ifdef PRINTF_VIA_SEMIHOSTING
    extern void initialise_monitor_handles(void);
#endif


void unityOutputStart()
{

#ifdef PRINTF_VIA_SEMIHOSTING
    initialise_monitor_handles();
#else
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIO);
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_UART);


    gpio_af_set(UART_TX_RX_GPIO, UART_TX_AF, UART_TX_GPIO_PIN);
    gpio_af_set(UART_TX_RX_GPIO, UART_RX_AF, UART_RX_GPIO_PIN);

    gpio_mode_set(UART_TX_RX_GPIO, GPIO_MODE_AF, GPIO_PUPD_PULLUP, UART_TX_GPIO_PIN);
    gpio_output_options_set(UART_TX_RX_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, UART_TX_GPIO_PIN);
    gpio_mode_set(UART_TX_RX_GPIO, GPIO_MODE_AF, GPIO_PUPD_PULLUP, UART_RX_GPIO_PIN);
    gpio_output_options_set(UART_TX_RX_GPIO, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, UART_RX_GPIO_PIN);

    /* USART configure BAUD_RATE 8N1 */
    usart_deinit(USART);
    usart_word_length_set(USART, USART_WL_8BIT);
    usart_stop_bit_set(USART, USART_STB_1BIT);
    usart_parity_config(USART, USART_PM_NONE);
    usart_baudrate_set(USART, BAUD_RATE);
    usart_receive_config(USART, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART, USART_TRANSMIT_ENABLE);
    usart_enable(USART);
#endif

}

void unityOutputChar(char c)
{
     usart_data_transmit(USART, c);
}

void unityOutputFlush() {}

void unityOutputComplete()
{

}