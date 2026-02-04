/*
 * UART.c
 *
 * Created: 2/1/2026 7:00:47 PM
 *  Author: willi
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "UART.h"

void UART_init(uint16_t ubrr)
{
	// Baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr & 0xFF);

	// 8N1: 8 bits, sin paridad, 1 stop
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	// Enable TX y RX
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void UART_txChar(char c)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void UART_txString(const char *s)
{
	while (*s)
	{
		UART_txChar(*s++);
	}
}

uint8_t UART_rx(void)
{
	return (UCSR0A & (1 << RXC0)) ? 1 : 0;
}

uint8_t UART_rxCharNoBloqueo(char *out)
{
	if (UART_rx())
	{
		*out = UDR0;
		return 1;
	}
	return 0;
}

char UART_rxCharBloqueo(void)
{
	while (!UART_rx());
	return UDR0;
}
