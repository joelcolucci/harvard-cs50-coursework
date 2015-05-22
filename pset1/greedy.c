/**
 * greedy.c
 *
 * Joel Colucci
 * JoelColucci@Gmail.com
 *
 * Program returns the minimum number of coins 
 * necessary to provide change to a customer
 */
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
int main(void)
{
    float changeAmount;
    
    // nest  a request for user input in a do while to ensure valid input
    do
    {
        printf("O hai! How much change is owed: \n");
        changeAmount = GetFloat();
    }
    while (changeAmount < 0.0);
    
    // convert number into cents taking into account float imprecision
    int inCents = round(changeAmount * 100.0);
    
    // code to optimize coins given
    
    int coinsGiven = 0;
    
    int array[4] = {25, 10, 5, 1};
    
    for (int i = 0; i < 4; i++)
    {
        if (inCents == 0)
        {
            break;
        }
        while (inCents >= array[i])
        {
            inCents -= array[i];
            coinsGiven++;
        }
    }

    printf("%i\n", coinsGiven);
    
    return 0;
}
