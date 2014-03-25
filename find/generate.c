/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // Verify that the user entered at least 1 argument, but no more than 2, else state usage.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Convert first argument to an integer.
    int n = atoi(argv[1]);

    // Seed rand() with either the users seed, or use the time seed function.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // Run the rand() fuction and print the output repeatedly until the number of cycles == the requested number of randoms.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // that's all folks
    return 0;
}
