#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "board.h"
#include "fsl_common.h"
#include "fsl_slcd.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"

#include "lcd.h"
#include "UART.h"

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) > (b)) ? (b) : (a))

// find gcd
int gcd(int a, int b) {
	if (b == 0)return a;
	return gcd(b, a % b);
}

typedef struct _PublicKey {
	int key;
} PublicKey;

typedef struct _PrivateKey {
	float key;
	int n;
} PrivateKey;

typedef struct _String {
	unsigned char* data;
	int size;
} String;

PrivateKey priv;

String* createString(const char* data)
{
	String* str = (String*)malloc(sizeof(String));
	str->size = strlen(data);
	str->data = (unsigned char*)malloc(str->size);
	memcpy(str->data, data, str->size);
	return str;
}

String* createStringFromData(const char* data, int size)
{
	String* str = (String*)malloc(sizeof(String));
	str->size = size;
	str->data = (unsigned char*)malloc(str->size);
	memcpy(str->data, data, str->size);
	return str;
}

String* createEmptyString(int size)
{
	String* str = (String*)malloc(sizeof(String));
	str->size = size;
	str->data = (unsigned char*)calloc(str->size, 1);
	return str;
}

String* createNULLString()
{
	String* str = (String*)malloc(sizeof(String));
	str->size = 0;
	str->data = 0;
	return str;
}

void setString(String* str, const char* data) {
	if (str->data)
		free(str->data);
	str->size = strlen(data);
	str->data = (unsigned char*)malloc(str->size);
	memcpy(str->data, data, str->size);
}

void setStringFromData(String* str, const char* data, int size) {
	if (str->data)
		free(str->data);
	str->size = size;
	str->data = (unsigned char*)malloc(str->size);
	memcpy(str->data, data, str->size);
}

void freeString(String* str)
{
	free(str->data);
	free(str);
}

void generateKeys(int p, int q, PublicKey* pub, PrivateKey* priv)
{
	int n = p * q;
	int track;
	int phi = (p - 1) * (q - 1);

	int nv = min((phi - 3), 16);
	int e = rand() % nv + 2;

	while (e < phi) {
		track = gcd(e, phi);
		if (track == 1)
			break;
		else
			e++;
	}
	priv->key = fmod(1.0 / e, (float)phi);
	priv->n = n;
	pub->key = e;
}

void encrypt(unsigned char msg, PublicKey* pub, unsigned char* encrypted)
{
	*(float*)encrypted = pow(msg, pub->key);
}

unsigned char decrypt(unsigned char* encrypted, PrivateKey* priv)
{
	return fmod(pow(*(float*)encrypted, priv->key), priv->n);
}


void encryptString(String* msg, PublicKey* pub, String* encrypted) {
	if (encrypted->data)
		free(encrypted->data);
	encrypted->size = msg->size * 4;
	encrypted->data = (unsigned char*)malloc(encrypted->size);
	for (int i = 0; i < msg->size; ++i) {
		encrypt(msg->data[i], pub, &(encrypted->data[4 * i]));
	}
}

void decryptString(String* encrypted, PrivateKey* priv, String* decrypted)
{
	if (decrypted->data)
		free(decrypted->data);
	decrypted->size = encrypted->size / 4;
	decrypted->data = (unsigned char*)malloc(encrypted->size);
	for (int i = 0; i < decrypted->size; ++i) {
		decrypted->data[i] = decrypt(&(encrypted->data[4 * i]), priv);
	}
}


// Main program running on the board
int main(void) {
	// initialize LCD and UART Communications
	init_lcd();
	BOARD_InitDebugConsole();

	// Python program waits to receive this mssage
	uart_puts("Initializing Board!...\n");

	// --------- Wait to receive number from python saying what the task is ---------
	while( 1 ) {
		char c1 = uart_recc();
		char c2 = uart_recc();
		char c3 = uart_recc();
		char c4 = uart_recc();

		// display the task number on the display
		displayDigit(1, c1 - 48);
		displayDigit(2, c2 - 48);
		displayDigit(3, c3 - 48);
		displayDigit(4, c4 - 48);
		LCD_TimeDelay(0xFFFFFFU);


		int task = c1 - 48;
		

		// --------- Generate Keys ---------
		if( task == 1 ) {	
			PublicKey pub;
			generateKeys(19, 11, &pub, &priv);	// p = 13 q = 11 (prime numbers)
			char key = pub.key;
			uart_putc(key);

		}

		// --------- Encrypt Message ---------
		if( task == 2 ) {
			// Receive public key and message length from user
			PublicKey publickey;
			publickey.key = uart_recc();
			uart_putc('1');
			char msg_len = uart_recc();
			uart_putc('1');

			String* message = createEmptyString(msg_len);

			// Receive message from user
			for(int i = 0; i < msg_len; i++ ) {
			    message->data[i] = uart_recc();
				uart_putc('1');
			}

			// Encrypt message and return it
			String* encrypted = createNULLString();
			encryptString(message, &publickey, encrypted);



			uart_putd((char*)encrypted->data, encrypted->size);


			LCD_TimeDelay(0xFFFFFFU);
		}

		// --------- Decrypt Message ---------
		if( task == 3 ) {
			// Receive message length from user
			char msg_len = uart_recc();
			uart_putc('1');

			String* message = createEmptyString(msg_len);

			// Receive message from user
			for(int i = 0; i < msg_len; i++ ) {
				message->data[i] = uart_recc();
				uart_putc('1');
			}

			String* decrypted = createNULLString();
			decryptString(message, &priv, decrypted);

			// send decrypted message back
			uart_putd((char*)decrypted->data, decrypted->size);
		}

		// display 0s when done task
		displayDigit(1, 0);
		displayDigit(2, 0);
		displayDigit(3, 0);
		displayDigit(4, 0);
		LCD_TimeDelay(0xFFFFFFU);	
	}
}
