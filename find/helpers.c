/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdbool.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    
    return false;
/*
	int beginning = 0;
	int ending = n - 1;

	//while length of list > 0
	while (ending >= beginning)
	{
		//look at middle of list
		int middle = (beginning + ending) / 2;
		if (values[middle] == value)
		{
			//if number found, return true
			return true;
		}

		//else if middle higher, search left
		else if (values[middle] > value)
		{
			ending = middle -1;
		}

		//else if middle lower, search right
		else
		{
			beginning = middle + 1;
		}

	}
	//return false
	return false;
*/
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // while the list is out of order
    for (int i = 0; i < n; i++)
    {
        int smallest = values[i];
        int smallest_location = i;
        
        // go through the entire list
        for (int j = i + 1; j < n; j++)
        {
            // find the smallest number
            if (smallest > values[j])
            {
                smallest = values[j];
                smallest_location = j;
            }
        }
            
        // put the beginning of the list where the smallest number was
        values[smallest_location] = values[i];
        
        // place it in the beginning of the list
        values[i] = smallest;
    }      
    return;
}
