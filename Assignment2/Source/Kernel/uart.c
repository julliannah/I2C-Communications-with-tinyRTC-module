#include "i2c.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// write content to a memory location
void mmio_write(uint32_t reg, uint32_t data) 
{
    *(volatile uint32_t*)reg = data;
};

// read content to a memory location
uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
};

uart_flags_t read_flags(void)
{
    uart_flags_t flags;
    flags.as_int = mmio_read(UART0_FR);
    return flags;
};

unsigned char uart_getc(void)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.receive_queue_empty);
    // What does the condition in the while loop mean?
    return mmio_read(UART0_DR);
};

void uart_putc(unsigned char c)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.transmit_queue_full);
    // What does the condition in the while loop mean?
    mmio_write(UART0_DR, c);
};

void uart_init(void)
{
    uart_control_t control;
    bzero(&control, 4);
    mmio_write(UART0_CR, control.as_int);
    // What is the purpose of the three previous lines?
    mmio_write(GPPUD, 0x00000000); // disable pin pull
    delay(150);    // provides the required set-up time for the control signal
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15)); // disable pins
    delay(150);    // provides the required hold time for the control signal
    mmio_write(GPPUDCLK0, 0x00000000);
    // What is the purpose of the five previous lines?
    mmio_write(UART0_ICR, 0x7FF); // sets all flags in the Interrupt Clear Register, hence it will clear all the pending UART interrupts.
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6)); // data received or sent have 8-bit long words.
    // disables all interrupts from the UART
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
                           (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
    // enable to receive and transmit data
    control.uart_enabled = 1;
    control.transmit_enabled = 1;
    control.receive_enabled = 1;
    mmio_write(UART0_CR, control.as_int);
}