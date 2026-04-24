/**
 * @file UART_periph_template.h
 * @author L. Nicholson-Andrews (lewisnich01@outlook.com)
 * @brief This is a template header file for any Peripheral to use
 */
#ifndef UART_PERIPH_TEMPLATE_H
#define UART_PERIPH_TEMPLATE_H

#include <stdint.h>

/* Defines for the Peripheral*/
#define <periph_name_base>      <base_address>
 
#define <periph_name_CR>        <offset>     /* Control Register */
#define <periph_name_SR>        <offset>     /* Status Register */
#define <periph_name_DR>        <offset>     /* Data register */

#define periph_name_BAUD_RATE   <baud_rate>  /* Baud Rate */


/* Declarations / Function Prototypes */
void <periph_name>_init(void);
void <periph_name>_open(void);
void <periph_name>_close(void);
void <periph_name>_write(uint8_t data);
uint8_t <periph_name>_read(void);

/* UART Data Structure */
typedef struct{
    uint32_t baud_rate;
    uint8_t  data_len;   
    int8_t  UART_PARITY    : 1;      /* 1 bit - even or odd */
    int8_t  UART_STOP_BITS : 1;      /* 1 bit - 1 or 2 stop bits */
} uart_comm_sett_t;

typedef enum{
    UART_INIT,
    UART_OPEN,
    UART_CLOSE,
    UART_READ,
    UART_WRITE
}uart_handle_t;


#endif /* UART_PERIPH_TEMPLATE_H */