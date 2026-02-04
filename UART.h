/*
 * UART.h
 *
 * Created: 2/1/2026 7:01:02 PM
 *  Author: willi
 */ 


#ifndef UART_H_
#define UART_H_


#include <stdint.h>

void UART_init(uint16_t ubrr);
void UART_txChar(char c);
void UART_txString(const char *s);

uint8_t UART_rx(void);
uint8_t UART_rxCharNoBloqueo(char *out);

char UART_rxCharBloquelo(void);


#endif /* UART_H_ */
