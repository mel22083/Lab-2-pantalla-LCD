/*
 * Labo2 dig2.c
 *
 * Created: 1/26/2026 6:48:16 PM
 * Author : willi
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "UART.h"

static LCD_printV(uint16_t adc)
{
	uint16_t v100 = (uint32_t)adc * 500UL/1023UL;
	uint8_t entero = v100 / 100;
	uint8_t decimal = v100 % 100;	
	
	LCD_caracter('0' + entero);
	LCD_caracter('.');
	LCD_caracter('0' + (decimal / 10));
	LCD_caracter('0' + (decimal % 10));
	LCD_caracter('V');
	
}

static void LCD_print1023(uint16_t x)
{
	LCD_caracter('0' + (x / 1000));        // miles
	LCD_caracter('0' + ((x / 100) % 10));  // centenas
	LCD_caracter('0' + ((x / 10) % 10));   // decenas
	LCD_caracter('0' + (x % 10));          // unidades
}	

static void LCD_printContador(int16_t c)
{
	if (c < 0)
	{
		LCD_caracter('-');
		c = -c;
	}
	LCD_caracter('0' + (c / 100) % 10);
	LCD_caracter('0' + (c / 10) % 10);
	LCD_caracter('0' + (c % 10));
}

int main(void)
{
	
	uint16_t S1, S2;
	int16_t S3 = 0;
	char rx;
	
	inicioLCD_8bits();
	init_ADC();
	UART_init(103);
	
	LCD_cursor(1,1);
	LCD_cadena("S1:");
	
	 LCD_cursor(1,2);
	 LCD_cadena("S2:");

	 LCD_cursor(12,1);   
	 LCD_cadena("S3:");

	while(1)
	{
	uint16_t S1 = leer_ADC(0);
	LCD_cursor(5,1);
	LCD_printV(S1);
	
	uint16_t S2 = leer_ADC(1);
	LCD_cursor(5,2);
	LCD_print1023(S2);
	
	if (UART_rxCharNoBloqueo(&rx))
	{
		if (rx == '+') S3++;
		else if (rx == '-') S3--;
	}
	
	LCD_cursor(12,2);
	LCD_printContador(S3);

	UART_txString("S1=");
	UART_txChar('0' + ((uint32_t)S1 * 5 / 1023));
	UART_txChar('.');
	UART_txChar('0' + (((uint32_t)S1 * 500 / 1023) % 100) / 10);
	UART_txChar('0' + (((uint32_t)S1 * 500 / 1023) % 10));
	UART_txString("V ");

	UART_txString("S2=");
	char buf[6];
	itoa(S2, buf, 10);
	UART_txString(buf);

	UART_txString(" S3=");
	itoa(S3, buf, 10);
	UART_txString(buf);
	UART_txString("\r\n");

	_delay_ms(200);
	
	}
}
