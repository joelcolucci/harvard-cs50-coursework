/**
 * vigenere.c
 *
 * Joel Colucci
 * JoelColucci@Gmail.com
 *
 * PSet2 Vigenere's Cipher
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void GenKeyArray(int key_array[], char wrd[], int wrd_len);
int EncipherChar(char p, int key);

int main(int argc, char *argv[])
{
    // validate command line arguments
    if (argc != 2)
    {
        printf("Error: Too few command line arguments.");
        return 1;
    }
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error: Argument contains non-alpha characters\n");
            return 1;
        }
    }
    
    // create array containing numerical representations for key word
    int key_len = strlen(argv[1]);    
    int key_array[key_len];
    GenKeyArray(key_array, argv[1], key_len);
    
    // input string from user
    string plain_text = GetString();
    
    // declare variable to act as index for alpha characters only
    int alpha_count = 0;
    
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        char p = plain_text[i];
        
        if (isalpha(p))
        {
            int key = key_array[alpha_count % key_len];
            printf("%c", EncipherChar(p, key));
            alpha_count++;
        }
        else
        {
            printf("%c", p);
        }
    }
    
    printf("\n");
    
    return 0;
}

void GenKeyArray(int key_array[], char wrd[], int wrd_len)
{
    for (int i = 0; i < wrd_len; i++)
    {
        char alpha_char = wrd[i];
        
        if (isupper(alpha_char))
        {
            key_array[i] = alpha_char - 'A';
        }
        else
        {
            key_array[i] = alpha_char - 'a';
        }
    }
}

int EncipherChar(char p, int key)
{
    int ascii_start;
    
    if (isupper(p))
    {
        ascii_start = 'A';
    }
    else
    {
        ascii_start = 'a';
    }
        
    int alpha_index = p - ascii_start;    
    int alpha = (alpha_index + key) % 26;
    int character = alpha + ascii_start;
    
    return character;
}
