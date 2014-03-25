/**
 * Test file for testing functions
 *
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void swap(int* a, int* b);

int d = 4;
int board[9][9];

int main(void)
{
    // Get board dimensions and populate grid with correct number of tiles plus 1 blank, swap '1' and '2' if tile count is odd.
    int tile = (d * d); //population of tiles
    int place = 1; //location helper, order starts at array 0 x 0.
    
    for (int i = 0; i <= (d - 1); i++) //iterate through rows.
    {
        for (int j = 0; j <= (d - 1); j++) //iterate through columns for each row.
        {
            if ((tile - place) == 0) //test if at the 0th place in population.
            {
                board[i][j] = 95; //set 'blank' space to ascii ' '.
                printf("board %i x %i = %c\n", i, j, board[i][j]);
            }
            else
            {
                board[i][j] = tile - place; //populate tile with declining tile set.
                place++;  //increment population.
                printf("board %i x %i = %i\n", i, j, board[i][j]);
            }
        }
    }
    int swaptest = (tile - 1) % 2;
    if (swaptest > 0) //test, true if tile count is odd. 
    {
        swap(&board[d-1][d-2], &board[d-1][d-3]);
        printf("board 3 x 1 = %i\n", board[d-1][d-3]);
        printf("board 3 x 2 = %i\n", board[d-1][d-2]);
    }
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;    
}
