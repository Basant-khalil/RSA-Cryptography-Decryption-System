#include "UART.h"
#include "board.h"

/*------------------------------*/
/* UART communication functions */
/*------------------------------*/
/* Initialize the UART for TX (115200, 8N1) */


void uart_putc (char ch)
{
	/* Wait until space is available in the FIFO */
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
	/* Send the character */
	UART0->D = (uint8_t)ch;
}

char uart_recc()
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	char ch = UART0->D;
	return ch;
}

void uart_puts(char *ptr_str)
{
    while(*ptr_str){
			/* Replace newlines with \r\n carriage return */
			if(*ptr_str == '\n') { uart_putc('\r'); }
      uart_putc(*ptr_str++);
		}
}

void uart_putd(char *ptr_str, int size)
{
    while(size--){
      uart_putc(*ptr_str++);
	}
    uart_putc('\r');
    uart_putc('\n');
}
