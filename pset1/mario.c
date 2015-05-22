/**
 * mario.c
 *
 * Joel Colucci
 * JoelColucci@Gmail.com
 *
 * pset1 program creates a pyramid out of "#"
 */
 
#include <stdio.h>
#include <cs50.h>
 
int main(void)
{
    int height;
    
    // get a height from user
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    int n = height;
    
    for (int i = 0; i < height; i++)
    {
        // print n - 1 spaces for each row
        for (int j = n - 1; j > 0; j--)
        {
            printf(" ");
        }
        
        // print  k + 1 # for each row until height
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        
        // print new line to start next row
        printf("\n");
        
        // decrement n
        n--;
    }

    return 0;
 }
