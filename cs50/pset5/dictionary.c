// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// You'll likely want to modify this and increase depending on your own implementation of hash function below
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp((cursor->word),word) == 0)
        {
            // in dictionary
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // will want to coordinate the modification of this hash and the int N 
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(input,"%s",word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word,word);
        n->next = NULL;
        int index = hash(word);
        if (table[index] ==  NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        word_count++;
    }
    fclose(input);
    return true;
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count != 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *ptr = NULL;
    node *cursor = NULL;
    
    for (int c = 0; c < N; c++)
    {
        for (cursor = table[c]; cursor != NULL; cursor = ptr)
        {
            ptr = cursor->next;
            free(cursor);
        }
        table[c] = NULL;
    } 
    return true;
}
