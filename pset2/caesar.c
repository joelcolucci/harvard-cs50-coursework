/**
 * Caesar.c
 * By Joel Colucci
 *
 * CS50 Problem Set 2
 * Caesar Cipher
 */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int EncipherText(char p, int key);

int main(int argc, char* argv[])
{
    // check that user entered correct # of cmd line args
    if (argc != 2)
    {
        printf("Error: Invalid amount of command line arguments.\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    
    // check that key is valid -> non-negative    
    if (argv[1] <= 0)
    {
        printf("Error: Invalid key entered. Keys must be non-negative");
        return 1;
    }
    
    // receive a character string from the user
    string plain_text = GetString();
    
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        char p = plain_text[i];
        
        if (isalpha(p))
        {
            printf("%c", EncipherText(p, key));
        }
        else
        {
            printf("%c", p);
        }
    }
    
    printf("\n");
    
    return 0;
}

int EncipherText(char p, int key)
{
    // declare variable to hold ascii value to assist in alpha char value
    int ascii_val; 
    
    if (isupper(p))
    {
        ascii_val = 'A';
    }
    else
    {
        ascii_val = 'a';
    }
        
    int alpha_index = p - ascii_val;
    int alpha = (alpha_index + key) % 26;
    int character = alpha + ascii_val; 
        
    return character;
}
