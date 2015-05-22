/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // binary search
    int high = n - 1;
    int low = 0;
    
    while (low <= high)
    {
        int mid = (high + low) / 2;
        
        if (value == values[mid])
        {
            return true;
        }
        else if (value < values[mid])
        {
            high = mid - 1;
        }
        else if (value > values[mid])
        {
            low = mid + 1;
        }
    }
    return false;   
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // insertion sort
    
    for (int i = 0; i < n; i++)
    {
        int element = values[i];
        int j = i;
        
        while (j > 0 && element < values[j - 1])
        {
            values[j] = values[j - 1];
            j--;
        }
        
        values[j] = element;
    }
    return;
}
