#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// This is a ciphertext program
// Requires user to provide the cipherkey as a command line argument = a positive integer
// pseudocode explanation of the program
// purpose of program is to encode standard text characters based on a simple substitution program
// for example a + 1 = b. Therefore, Dadbod = Dbecbe

// program will check the contents of (k) and reject any inputs with an error message.
// ask User to input the plaintext version of the text that they would like to encode using printf.
// check values of each character in the plaintext
// each character will be encoded based on the value of (k)
// Print "ciphertext:"
// if the character is lower case, an encoded lowercase character will be printed
// if the character is upper case, an encoded uppercase character will be printed
// if the character is not alphanumeric, print it as plaintext.
// print a new line.

int main(int argc, string argv[])
{
    // need to reject any argv that is not a single argument.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // converting argv key into an integer for use as a key.
    int c = atoi(argv[1]);
    // rejecting any invalid numbers
    if (c == '\0' || c < 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // rejecting arguments that include a mix of alphabet and numbers
    int k = strlen(argv[1]);
    for (int i = 0; i < k; i++)
    {
        char e = argv[1][i];
        if (isalpha(e))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // commenting out this argv confirmation step - printf("%i\n", c);

    // user asked for plaintext input of text that they need encoded
    string plaintext = get_string("plaintext:  ");
    int plainlen = strlen(plaintext);
    
    // printing the cipher section.
    // the if loops allow for lower case and upper case values to stay within range, even with large size keys.
    // basically works by converting character to int ascii value, then encoding it agasinst the c value, and returning it to ascii value.
    printf("ciphertext: ");
    for (int m = 0; m < plainlen; m++)
    {
        char z = plaintext[m];
        if (islower(z))
        {
            char x = z - 97;
            char y = ((x + c) % 26) + 97;
            printf("%c", y);
        }
        else if (isupper(z))
        {
            char w = z - 65;
            char v = ((w + c) % 26) + 65;
            printf("%c", v);
        }
        else
        {
            printf("%c", z);
        }
    }
    //closing program neatly
    printf("\n");
    return 0;
}
