/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

#define SIZE 2500

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}node;

int size_of_dict = 0;
bool loaded = false;
node* hash_table[SIZE];



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // figure out what "bucket" to check
    int value = hash_function(word, SIZE);
    
    // go to that bucket
    node* hash_node = hash_table[value];
    
    // traverse the list
    while (hash_node != NULL)
    {
        if (strcasecmp(hash_node->word, word) == 0)
        {
            return true;
        }
        else
        {
            hash_node = hash_node->next;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    while (true)
    {
        // create a node to store word
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        // pull in a word until end of file
        if (fscanf(file, "%s", new_node->word) == EOF)
        {
            free(new_node);
            break;
        }
        
        // hash new_now->word
        int value = hash_function(new_node->word, SIZE);
        
        // insert into hash table
        if (hash_table[value] == NULL)
        {
            hash_table[value] = new_node;
            new_node->next = NULL;
        }
        else
        {
            // insert at front of linked list
            new_node->next = hash_table[value];
            hash_table[value] = new_node;
        }
        
        size_of_dict++;
    }

    loaded = true;

    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return (loaded == true) ? size_of_dict : 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    
    for (int i = 0; i < SIZE; i++)
    {
        node* crawler = hash_table[i];
        node* curr = NULL;
        while (crawler != NULL)
        {
            curr = crawler;
            crawler = curr->next;
            free(curr);
        }
    }
 
    return true;

    return false;
}

/**
 * hash function from cs50 Study
 * src: https://study.cs50.net/hashtables
 */
int hash_function(const char* key, int size)
{
    // initialize index to 0
    int index = 0;

    // sum ascii values
    for (int i = 0; key[i] != '\0'; i++)
    {
        index += toupper(key[i]);
    }

    // mod by size to stay w/in bound of table
    return index % size;
}

