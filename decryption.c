#include <stdio.h>
#include <string.h>
#include <math.h>

/* take 2 numbers and do base^ exponent mod n */
int power (int base, int exponent){
	int result = base;
	int i;
	for (i=1; i<exponent;i++){
		result = result * base;
		result = result % 33;
	}
	return result;
}


// For this project the public key will be n = 33 and e = 7.
// The private key is d = 3, p = 3, and q = 11. Phi = 20
int n = 33;
int e =7;
int d = 3;
int p = 3;
int q = 11;
int phi = 20;

/*decrypt one single letter such as D to be B
 * process is:
 * 1) find the index the letter corresponds to by calling change_letter_to_index			D -> number
 * 2) do the decryption process on the index by doing index^3 mod 33									num^p mod n
 * 3) change the result integer to the corresponding letter by calling change_index_to_letter and output that*/
char one_letter_decryption (char input_letter){
	int index = change_letter_to_index (input_letter);
	int number = power (index, 3) % 33;
	return change_index_to_letter(number);
}

// Add a character into a string
void append(char* s, char c) {
	int len = strlen( s );	// finds the length of the string
    s[ len ] = c;			// appends the character
    s[ len + 1 ] = '\0';	// moves the null terminator over
}

// ------------------------------------------------------------------------------------
// decrypt_main_word: Decrypt the whole input decrypting each letter in
// it using a loop output the accumulated string at the end
// ------------------------------------------------------------------------------------
void decrypt_main_word (char* input, char* output, int n){
	// Lets the program thinks the length of the string is 0
	output[0] = '\0';

	// doesn't return because we send pointer to result
	for (int i = 0; n; i++) {
		append(output, one_letter_decryption(input[i]));
	}
}