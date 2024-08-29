#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



string key;
int key_length;
int validated_key;

// prototype
char rotate(char c, int validated_key);


int main(int argc, string argv[])
{
    // expecting 1 argument to be passed in
    while (argc != 2)
	{
        printf("Usage: ./caesar key\n");
        return 1;
	}

    key = argv[1];
    key_length = strlen(key);
    for (int i = 1; i < key_length; i++)
    {
        // fail if any char passed as argument isn't a digit
        if (!isdigit((int) key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // convert string passed as argument to integer
    validated_key = atoi(key);
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    int plaintext_length = strlen(plaintext);
    // iterate through each char in string
    for (int c = 0; c < plaintext_length; c++)
    {
        char char_to_pass = plaintext[c];
        char rotated_char = (rotate(char_to_pass, validated_key));
        printf("%c", rotated_char);

    }
    printf("\n");
}

// function to rotate the char by the amount passed in the initial argument
char rotate(char passed_char, int validated_key)
{
    if (!isalpha(passed_char))
    {
        return passed_char;
    }
    else
    {
        char rotated = passed_char - validated_key;
        if ((isupper(passed_char) && (int) rotated < 65) || (islower(passed_char) && (int) rotated < 97))
        {
            // loop back around to the end of the alphabet if before A
            rotated = (rotated + 26);
            return rotated;
        }
        else
        {
            return rotated;
        }
    }
}
