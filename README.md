## Your Project Answers

### Project Description

Project Idea:

decryption using leds: ask the user to input some text input through the laptop that would be connected to the laptop and then we decrypt that message and output the resulting value in binary using the LEDs to signal that. 

We would like to implement RSA cryptography to decrypt a plain text message provided by the user. We would then display the decrypted message in binary using five LEDs. The way we can do this is if we have the form 11000 and we use the blue led to represent the first digit and the green to represent the second then we just blink the blue and the green to signal they are ones. 
### Technical Approach

Plan to use a computer and five LEDs as external peripherals. The computer will be used as a way to allow the user to enter a string of text that will be sent to the board to encrypt. Then the board, connected to the LEDs, will display the decrypted text.  

In RSA, we will choose 2 prime numbers p and a and use them to calculate n=pq. Then we will pick 2 numbers e and d such that ed= 1 mod (p-1)(q-1)

We will make public n and e and make p,q and d private. When we receive the message m, we will calculate m^d mod n to output a decrypted message. 

The high level idea then is :

* input the text you would like through the laptop where we will limit the maximum number of words to be 4 and each word has maximum length of 6 words 

* Change the text inputted to its binary equivalent where we use 5 bits for every alphabet letter. For instance 00001 becomes a.

* Calculate the output value a knowing d and n 

* Output that value a through signaling the needed LEDs. 
Plan to use a computer and five LEDs as external peripherals. The computer will be used as a way to allow the user to enter a string of text that will be sent to the board to encrypt. Then the board, connected to the LEDs, will display the decrypted text.  

In RSA, we will choose 2 prime numbers p and a and use them to calculate n=pq. Then we will pick 2 numbers e and d such that ed= 1 mod (p-1)(q-1)

We will make public n and e and make p,q and d private. When we receive the message m, we will calculate m^d mod n to output a decrypted message. 

The high level idea then is :

* input the text you would like through the laptop where we will limit the maximum number of words to be 4 and each word has maximum length of 6 words 

* Change the text inputted to its binary equivalent where we use 5 bits for every alphabet letter. For instance 00001 becomes a.

* Calculate the output value a knowing d and n 

* Output that value a through signaling the needed LEDs. 

## Feedback.

Cool. The encryption aspect and keeping the private key on the baord is neat! I don't think the output LEDs should give you any trouble, but you could also use the LCD in a pinch. 

## Welcome team! Please edit me.
### You can use the 'main' branch for you code.
### The GitHub web-page should be in the 'gh-pages' branch
You can access the page adding a "pages" prefix to the url for the git repo e.g. if your browser currently shows https://github.coecis.cornell.edu/ece3140-sp22/bak94-gb438-sk2446 then the GitHub page is at https://pages.github.coecis.cornell.edu/ece3140-sp22/bak94-gb438-sk2446 . You can edit the source in the gh-pages branch or use the "automatic page generator" acessible via settings->options in the GitHub Pages Section toward the bottom. We recommend the latter approach since it is quick and easy. We made an initial wepage that you can edit and a description of the headings we expect to see.
