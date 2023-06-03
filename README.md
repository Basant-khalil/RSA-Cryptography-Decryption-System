## Project Idea:

LED-Based Decryption System: The objective of this project is to develop a sophisticated decryption system using Light Emitting Diodes (LEDs). Users will input a plaintext message via a laptop interface, which will be securely transmitted to the decryption device. The device will employ RSA cryptography to decrypt the message and then visually represent the resulting binary value using a set of precisely controlled LEDs.

## Technical Approach:
Our technical approach involves utilizing a computer as the central processing unit and integrating it with five high-intensity LEDs as external peripherals. The laptop interface will serve as the user's input gateway, enabling the entry of plaintext messages. Once received, the message will be securely transmitted to the decryption device for processing. The decrypted output will be displayed through the synchronized control of the connected LEDs, ensuring accurate visualization of the binary representation.

In the RSA decryption process, we will follow these key steps:

Key Generation:
a. Two large prime numbers, p and q, will be carefully chosen to ensure robust security.
b. The modulus, n, will be calculated as the product of p and q: n = p * q.
c. Two additional numbers, e and d, will be selected to satisfy the condition e * d ≡ 1 (mod (p-1)(q-1)).

Encryption:
a. The public key, consisting of n and e, will be made available for encryption purposes.
b. The private key, comprising p, q, and d, will be strictly kept confidential.
c. Upon receiving a plaintext message, denoted as m, the device will utilize the public key to calculate m^d mod n, resulting in the encrypted message.

LED-Based Decryption:
a. The laptop interface will accept the user's desired plaintext input, imposing constraints of up to four words with a maximum word length of six characters.
b. An intricate binary conversion algorithm will be employed to represent each character of the input text using precisely five bits.
c. The decrypted output, denoted as 'a', will be calculated using the provided private key values of d and n.
d. The resulting value 'a' will be accurately conveyed to the user by illuminating the appropriate LEDs, meticulously synchronized to represent the binary signal.

Through the intricate integration of computational power, advanced cryptography algorithms, and precise LED control, our project aims to deliver an efficient and visually intuitive decryption system, providing users with a secure means to transmit and visualize confidential messages.


The github page is at: 
