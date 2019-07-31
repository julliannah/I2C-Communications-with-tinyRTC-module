#ifndef __I2C__
#define __I2C__
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Adress map of Master
enum {
    GPIO_BASE    = 0x7F200000,
    // GPPUD        = (GPIO_BASE + 0x94),
    // GPPUDCLK0    = (GPIO_BASE + 0x98),
    SPI0_BASE    = (GPIO_BASE + 0x4000), // SPI Master Base address
    SPI0_CS      = (SPI0_BASE + 0x00),   // Control and Status
    SPI0_FIFO    = (SPI0_BASE + 0x04),   // TX and RX FIFOs
    SPI0_CLK     = (SPI0_BASE + 0x08),   // Clock Divider
    SPI0_DLEN    = (SPI0_BASE + 0x0C),   // Data Length
    SPI0_LTOH    = (SPI0_BASE + 0x10),   // SPI LOSSI mode TOH
    SPI0_DC      = (SPI0_BASE + 0x14),   // SPI DMA DREQ Controls
};

// Adress map of Slave
enum
{
    GPIO_BASE    = 0x3F210000,
    // GPPUD        = (GPIO_BASE + 0x94),
    // GPPUDCLK0    = (GPIO_BASE + 0x98),
    I2C_SPI_SLV_BASE     = (GPIO_BASE + 0x4000), // SPI Slave Base address
    I2C_SPI_SLV_DR       = (I2C_SPI_SLV_BASE + 0x00),  // Data Register
    I2C_SPI_SLV_RSR      = (I2C_SPI_SLV_BASE + 0x04),  // Receive Status Register / Error Clear Register
    I2C_SPI_SLV_SLV      = (I2C_SPI_SLV_BASE + 0x08),  // Address Register holds the I2C slave address value
    I2C_SPI_SLV_CR       = (I2C_SPI_SLV_BASE + 0x0C),  // Control Register
    I2C_SPI_SLV_FR       = (I2C_SPI_SLV_BASE + 0x10),  // Flag Register
    I2C_SPI_SLV_IFLS     = (I2C_SPI_SLV_BASE + 0x14),  // Interrupt fifo level select register
    I2C_SPI_SLV_IMSC     = (I2C_SPI_SLV_BASE + 0x18),  // Interrupt Mask Set / Clear Register
    I2C_SPI_SLV_RIS      = (I2C_SPI_SLV_BASE + 0x1C),  // Raw Interrupt Status Register
    I2C_SPI_SLV_MIS      = (I2C_SPI_SLV_BASE + 0x20),  // Masked Interrupt Status Register
    I2C_SPI_SLV_ICR      = (I2C_SPI_SLV_BASE + 0x24),  // Interupt Clear Register
    I2C_SPI_SLV_DMACR    = (I2C_SPI_SLV_BASE + 0x28),  // Disable DMA Control Register
    I2C_SPI_SLV_TDR      = (I2C_SPI_SLV_BASE + 0x2C),  // FIFO Test Data
    I2C_SPI_SLV_GPUSTAT  = (I2C_SPI_SLV_BASE + 0x30),  // GPU Status Register
    I2C_SPI_SLV_HCTRL    = (I2C_SPI_SLV_BASE + 0x34),  // Host Control Register
    I2C_SPI_SLV_DEBUG1   = (I2C_SPI_SLV_BASE + 0x38),  // I2C Debug Register
    I2C_SPI_SLV_DEBUG2   = (I2C_SPI_SLV_BASE + 0x3C),  // SPI Debug Register
} ;

typedef union uart_flags
{
    struct
    {
        uint8_t clear_to_send : 1;
        uint8_t data_set_ready : 1;
        uint8_t data_carrier_detected : 1;
        uint8_t busy : 1;
        uint8_t receive_queue_empty : 1;
        uint8_t transmit_queue_full : 1;
        uint8_t receive_queue_full : 1;
        uint8_t transmit_queue_empty : 1;
        uint8_t ring_indicator : 1;
        uint32_t padding : 23;
    };
    uint32_t as_int;
} uart_flags_t;

typedef union uart_control
{
    struct
    {
        uint8_t uart_enabled : 1 ;
        uint8_t sir_enabled : 1;
        uint8_t sir_low_power_mode : 1;
        uint8_t reserved : 4;
        uint8_t loop_back_enabled : 1;
        uint8_t transmit_enabled : 1;
        uint8_t receive_enabled : 1;
        uint8_t data_transmit_ready : 1;
        uint8_t request_to_send : 1;
        uint8_t out1 : 1;
        uint8_t out2 : 1;
        uint8_t rts_hardware_flow_control_enabled : 1;
        uint8_t cts_hardware_flow_control_enabled : 1;
        uint16_t padding;
    };
    uint32_t as_int;
     
} uart_control_t;

void mmio_write(uint32_t reg, uint32_t data);   
uint32_t mmio_read(uint32_t reg);               // read content to a memory location
void uart_init(void);
void uart_putc(unsigned char c);
uart_flags_t read_flags(void);
unsigned char uart_getc(void);
    
#endif