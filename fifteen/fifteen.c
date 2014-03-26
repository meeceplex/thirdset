/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// Char __ for use as blank space
char SP;

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void swap(int *a, int *b);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
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
                board[i][j] = 95; //set 'blank' space to ascii '__'.
            }
            else
            {
                board[i][j] = tile - place; //populate tile with declining tile set.
                place++;  //increment population.
            }
        }
    }
    
    int swaptest = (tile - 1) % 2; // variable equal to remainder of 'tile count sans the underscore tile' / 2.
    if (swaptest > 0) //test, true if tile count is odd. 
    {
        swap(&board[d-1][d-2], &board[d-1][d-3]);
    }
}

/**
 * Swap function
 */
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;    
} 


/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i <= (d - 1); i++) //iterate through rows.
    {
        for(int j = 0; j <= (d - 1); j++) //iterate through columns for each row.
        {
            if(board[i][j] == 95)
            {
                printf("%2c  ", 95);
            }
            else
            {
                printf("%2d  ", board[i][j]); //print current place.
            }
        }
        printf("\n"); //print new line.
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // Verify tile location as adjacent to blank tile, then swap tiles, else return false.
    int br = d; // Blank tile row coordinate
    int bc = d; // Blank tile column coordinate
    int tr = 0; // Move tile row coordinate
    int tc = 0; // Move tile column coordinate
    
    // Find coordinates of blank tile
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == 95)
            {
                br = i;
                bc = j;
            }
        }
    }
    
    // Find coordinates of move tile
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                tr = i;
                tc = j;
            }
        }
    }
    
    // Calculate difference from sum of coordinates, check if greater than 1 or -1
    int blanksum = (br + bc);
    int tilesum = (tr + tc);
    
    if(((blanksum - tilesum) == 1) || (blanksum - tilesum) == -1)
    {
        swap(&board[br][bc], &board[tr][tc]);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Check array for win configuration and return true, else return false
    
    int won = 0; // counter.
    
    for(int i = 0; i < d; i++) // iterate through rows.
    {
        for(int j = 0; j < d; j++) // iterate through columns.
        {
            if(board[i][j] == (won + 1)) // check if current position is 1 greater than previous, and proceed.
            {
                won++;
                if(won == ((d * d) - 1) && (board[d - 1][d - 1] == 95)) // if board is in winning configuration, return true.
                return true;
            }
        }
    }
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
