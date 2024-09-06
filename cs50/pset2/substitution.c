#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

string key;
int key_length;
int validated_key;
int dupe_count;
int char_int;

int main(int argc, string argv[])
{
    // expecting 1 argument to be passed in
    while (argc != 2)
	{
        printf("key must contain 1 argument\n");
        return 1;
	}

    key = argv[1];
    key_length = strlen(key);
    // fail if key doesn't contain 26 characters
    if (key_length != 26)
    {
        printf("key must contain 26 characters!\n");
        return 1;
    }
    // printf("key: %s  | key_length: %i\n", key, key_length);

    for (int i = 0; i < key_length; i++)
    {
        // fail if key isn't alphabetic
        if (!isalpha(key[i]))
        {
            printf("key must contain only alphabetic characters\n");
            return 1;
        }

        // check if contains duplicate characters
        dupe_count = 0;
        for (int d = 0; d < key_length; d++)
        {
            if (key[i] == key[d])
            {
                dupe_count++;
            }
        }
        if (dupe_count >= 2)
        {
            printf("key contains duplicate characters\n");
            return 1;
        }
    }
    // printf("passed validation successfully\n");

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    // iterate through each char in plaintext string
    int plaintext_length = strlen(plaintext);
    for (int c = 0; c < plaintext_length; c++)
    {
        // get int of char and it's distance from A as int then print uppercase of key[distance int]
        if (isupper(plaintext[c]))
        {
            char_int = (int) plaintext[c] - 65;
            printf("%c", toupper(key[char_int]));
        }
        // get int of char and it's distance from a as int then print lowercase of key[distance int]
        else if (islower(plaintext[c]))
        {
            char_int = (int) plaintext[c] - 97;
            printf("%c", tolower(key[char_int]));
        }
        else
        {
            printf("%c", plaintext[c]);
        }
    }
    printf("\n");
}