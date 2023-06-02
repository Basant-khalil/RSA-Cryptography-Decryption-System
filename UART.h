#ifndef UART_h
#define UART_h

/*------------------------------*/
/* UART communication functions */
/*------------------------------*/
/* Initialize the UART for TX (115200, 8N1) */


void uart_putc (char ch);

char uart_recc();

void uart_puts(char *ptr_str);

void uart_putd(char *ptr_str, int size);

#endif
