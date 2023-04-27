#include "unity_config.h"
#include "gd32f3x0.h"
#include <stdio.h>

/* delay routines for initial startup delay */
volatile static unsigned long delay;
void SysTick_Handler(void) {
    if (0U != delay)
        delay--;
}
void startup_delay(unsigned long ms) {
    SysTick_Config(SystemCoreClock / 1000U);
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
    delay = ms;
    while (0U != delay);
}

/* settings for USART0 alternate settings, TX = PB6, RX = PB7 */
#define RCU_GPIO RCU_GPIOB
#define RCU_UART RCU_USART0
#define USART USART0
#define UART_TX_RX_GPIO GPIOB
#define UART_TX_GPIO_PIN GPIO_PIN_6
#define UART_RX_GPIO_PIN GPIO_PIN_7
#define UART_TX_AF  GPIO_AF_0 /* PB6 AF0 is USART0_TX */
#define UART_RX_AF  GPIO_AF_0 /* PB7 AF0 is USART0_RX */

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

    // if we don't want to manually press the reset the button, we have to have a little delay here
    // otherwise the output will be over before PlatformIO even opened the serial port...
    // for slower systems, this value may need to be higher.
    startup_delay(2000);
}

void unityOutputChar(char c)
{
    usart_data_transmit(USART, c);
    while(usart_flag_get(USART, USART_FLAG_TBE) != SET) {}
}

void unityOutputFlush() {
}

void unityOutputComplete()
{
    /* we could deinitialize the USART here if we cared */
    /* usart_disable(USART); */
}