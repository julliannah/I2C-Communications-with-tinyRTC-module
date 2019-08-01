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
    BSC0_BASE    = (GPIO_BASE + 0x5000), // BSC Master Base address
    BSC0_C       = (BSC0_BASE + 0x00),   // Control
    BSC0_S       = (BSC0_BASE + 0x04),   // Status
    BSC0_DLEN    = (BSC0_BASE + 0x08),   // Data Length
    BSC0_A       = (BSC0_BASE + 0x0C),   // Slave Address
    BSC0_FIFO    = (BSC0_BASE + 0x10),   // Data FIFO
    BSC0_DIV     = (BSC0_BASE + 0x14),   // Clock Divide
    BSC0_DEL     = (BSC0_BASE + 0x18),   // Data Delay
    BSC0_CLKT    = (BSC0_BASE + 0x1C),   // Clock Stretch Timeout

};

// typedef union uart_flags
// {
//     struct
//     {
//         uint8_t clear_to_send : 1;
//         uint8_t data_set_ready : 1;
//         uint8_t data_carrier_detected : 1;
//         uint8_t busy : 1;
//         uint8_t receive_queue_empty : 1;
//         uint8_t transmit_queue_full : 1;
//         uint8_t receive_queue_full : 1;
//         uint8_t transmit_queue_empty : 1;
//         uint8_t ring_indicator : 1;
//         uint32_t padding : 23;
//     };
//     uint32_t as_int;
// } uart_flags_t;

typedef union master_control
{
    struct
    {
        uint8_t transmit_read : 1;
        uint8_t fifo_clear : 2;
        uint8_t transmit_start : 1;
        uint8_t transmit_start : 1;
        uint8_t transmit_start : 1;
        uint8_t done_interrupt : 1;
        uint8_t transmit_interrupt : 1;
        uint8_t receive_interrupt : 1;
        uint8_t master_enabled : 1 ;
        // uint8_t sir_enabled : 1;
        // uint8_t sir_low_power_mode : 1;
        // uint8_t reserved : 4;
        // uint8_t loop_back_enabled : 1;
    };
    uint32_t as_int;
     
} master_control_t;

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

typedef union slave_flags
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

typedef union slave_control
{
    struct
    {
        uint8_t slave_enabled : 1 ;
        uint8_t spi_mode : 1;
        uint8_t i2c_mode : 1;
        uint8_t clock_phase : 1;
        uint8_t clock_polarity : 1;
        uint8_t status_enabled : 1;
        uint8_t control_enabled : 1;
        uint8_t break_current : 1;
        uint8_t transmit_enabled : 1;
        uint8_t receive_enabled : 1;
        uint8_t inverse_rx_flags : 1;
        uint8_t fifo_enabled : 1;
        uint8_t host_control_enabled : 1;
        uint8_t inverse_tx_flags : 1;
    };
    uint32_t as_int;
     
} slave_control_t;

void mmio_write(uint32_t reg, uint32_t data);   
uint32_t mmio_read(uint32_t reg);               // read content to a memory location
void uart_init(void);
void uart_putc(unsigned char c);
uart_flags_t read_flags(void);
unsigned char uart_getc(void);
    
#endif