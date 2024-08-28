#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int sentences = 0;
int letters = 0;
int words = 1;
char current;
char previous;

int main(void)
{
    string text = get_string("Text: ");

    int length = strlen(text);
    printf("\nlength = %i  |  ", length);

    // loop through each char
    for (int i = 0; i < length; i++)
    {
        // this section keeps track of previous letter to help determine word count
        if (current == 'y')
        {
            previous = 'y';
        }
        if (current == 'n')
        {
            previous = 'n';
        }

        current = 'x';

        if (text[i] == ' ')
        {
            current = 'y';
        }
        else
        {
            current = 'n';
        }
        
        // if previous is not a space char and current is a space char, then add +1 to word count
        if (previous == 'n' && current == 'y')
        {
            words += 1;
        }

        // calculate total sentences
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences += 1;
        }
        
        // calculate total letters
        if (isalpha(text[i]))
        //if (text[i] != '.' && text[i] != '?' && text[i] != '!' && text[i] != ' ')
        {
            letters += 1;
        }


    }
    printf("sentences = %i  |  ", sentences);
    printf("letters = %i  |  ", letters);
    printf("words = %i  |  ", words);

    // Compute the Coleman-Liau index
    //index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text
    float L = ((float) letters / (float) words) * 100.0;
    printf("L = %f  |  ", L);
    float S = ((float) sentences / (float) words) * 100.0;
    printf("S = %f  |  ", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("index = %f  |  ", index);

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}
