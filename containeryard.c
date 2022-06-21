#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

/* Purpose: Initialise the floor yard as a 2D array
Input: 2D array of the floor data, the entry point, position of entry point
Output: void
Author: Matthew Wai

Iterate through each cell
*/

void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if ((i == 0 || i == NUM_ROWS - 1) || (j == 0 || j == NUM_COLS - 1)) // If the cell is on the boarders of the 2D array
            {
                floor[i][j] = BOUNDARY; // Set that cell to the value of BOUNDARY
            }
            else
            {
                floor[i][j] = VACANT; // else set the cell to the value to VACANT
            }
        }
    }
    if (entryboundary == 'T') // If input entry is T, set the entarance and exit
    {
        floor[0][index] = ENTRY;
        floor[NUM_ROWS - 1][index] = EXIT;
    }
    else if (entryboundary == 'B') // If input entry is B, set the entarance and exit
    {
        floor[NUM_ROWS - 1][index] = ENTRY;
        floor[0][index] = EXIT;
    }

    else if (entryboundary == 'L') // If input entry is L, set the entarance and exit
    {
        floor[index][0] = ENTRY;
        floor[index][NUM_COLS - 1] = EXIT;
    }

    else if (entryboundary == 'R') // If input entry is R, set the entarance and exit
    {
        floor[index][NUM_COLS - 1] = ENTRY;
        floor[index][0] = EXIT;
    }
}

/*
Purpose: To print the floor
Input: 2D array of floor
Output: void
Author: Matthew Wai

Iterates through each cell
*/

void PrintFloor(int floor[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (floor[i][j] == ENTRY) // If the value of this cell is ENTRY, print U
            {
                printf("U");
            }

            else if (floor[i][j] == EXIT) // If the value of this cell is EXIT, print X
            {
                printf("X");
            }

            else if (floor[i][j] == BOUNDARY) // If the value of this cell is BOUNDARY, print @
            {
                printf("@");
            }

            else if (floor[i][j] == VACANT) // If the value of this cell is VACANT, print a space
            {
                printf(" ");
            }
            else
            {
                printf("%c", floor[i][j]); // Print the letters of the containers
            }
        }
        printf("\n");
    }
}
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width)
{
    // Purpose: This function calculates the area of the floor in ft
    // Inputs: 2D array of floor yard, cell length, cell width
    // Outputs: The area of the floor by multiplying the area of each cell by the total number of grid cells
    // Author: Matthew Wai
    //
    // Sets the formula for a cell area to the length multiplied by width
    double cell_area = length * width;
    int empty_cells = 0;

    // Iterates through each cell
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (floor[i][j] == VACANT) // If the pixel is VACANT then increase thenumber of empty cells by 1
            {
                empty_cells++;
            }
        }
    }
    // Calculate the area of empty cells and return that area
    double available_area = cell_area * empty_cells;
    return available_area;
}

/*
Purpose: Add a conatiner in alphabetical order to the empty spaces of the floor
Input: 2D array of floor, the position to add the container, the size of the conatiner, and the direction of placement
Output: void
Author: Matthew Wai
*/

void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction)
{
    // Set the first conatiner to be placed as label A
    char container = 65;
    // Iterate through all the cells to check if a letter has already been placed, if it has, place the next letter
    for (int i = 1; i < NUM_ROWS - 1; i++)
    {
        for (int j = 1; j < NUM_COLS - 1; j++)
        {
            if (floor[i][j] + 1 > container)
                container = floor[i][j] + 1;
        }
    }

    // Get the co-ordinates in the 2D array from the position to place the container
    int row_pos, col_pos;

    row_pos = (position / NUM_ROWS);
    col_pos = (position % NUM_COLS);

    if (direction) // Vertical placement of the container
    {
        for (int x = 0; x < size; x++)
        {
            if (floor[row_pos + x][col_pos] != VACANT)
            {
                return;
            }
        }

        for (int x = 0; x < size; x++)
        {
            floor[row_pos + x][col_pos] = container;
        }
    }

    else // Horizontal placement of the container
    {
        for (int x = 0; x < size; x++)
        {
            if (floor[row_pos][col_pos + x] != VACANT)
            {
                return;
            }
        }

        for (int x = 0; x < size; x++)
        {
            floor[row_pos][col_pos + x] = container;
        }
    }
}

/*
Purpose: Locate and store the location on specific containers
Input: 2D array of floor, character of container, start and end positions of the containers
Output: A boolean value indicating whether the containers movement is block (0), or vacant (1)
Author: Matthew Wai
*/
int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd)
{
    int length = 0;
    int blocked = 0;
    int row[100] = {0};
    int col[100] = {0};

    // Iterate through the floor and find the characters move and store their length and location
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (floor[i][j] == move)
            {
                // Finds the length of the container
                length++;
                row[length] = i;
                col[length] = j;
            }
        }
        // Find the start and end of the container
        for (int x = 1; x < (length + 1); x++)
        {
            if (x == 1)
            {
                *rowStart = row[x];
                *colStart = col[x];
            }
            if (x == length)
            {
                *rowEnd = row[x];
                *colEnd = col[x];
            }
        }
    }
    // If horizontal, check the if blocked in the horizontal direction
    if ((row[1] == row[2]) && (((floor[*rowStart][*colStart - 1] && floor[*rowStart][*colEnd + 1])) == VACANT))
    {
        blocked = 1;
    }
    // If vertical, check the if blocked in the vertical direction
    else if ((col[1] == col[2]) && (((floor[*rowStart - 1][*colStart] && floor[*rowEnd + 1][*colStart])) == VACANT))
    {
        blocked = 1;
    }
    else
    {
        blocked = 0;
    }

    return blocked;
}

/*
Purpose: Moves the containers if the are not blocked
Input: 2d array of containers floor, start and end positions of container, boolean expression if the container is blocked
Output: 2 if the container reaches an exit, 1 if it reaches a entrance otherwise 0
Author: Matthew Wai
*/
int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked)
{
    if ((r0 == r1) && (isBlocked == 1)) // Horizontal & Not blocked
    {
        if (floor[r0][c0 - 1] != VACANT) // If Left is blocked
        {
            while (floor[r0][c1 + 1] == VACANT) // Move container right
            {
                floor[r0][c0] = VACANT;
                floor[r0][c1 + 1] = floor[r1][c1];
                c1++;
                c0++;
            }
        }
        else
        {
            while (floor[r0][c0 - 1] == VACANT) // Move container left
            {
                floor[r0][c1] = VACANT;
                floor[r0][c0 - 1] = floor[r0][c0];
                c0--;
                c1--;
            }
        }
    }

    else if ((c0 == c1) && (isBlocked == 1)) // Vertical & Not blocked
    {
        if (floor[r0 - 1][c0] != VACANT) // If Up is blocked
        {
            while (floor[r1 + 1][c0] == VACANT) // Move container down
            {
                floor[r0][c0] = VACANT;
                floor[r1 + 1][c0] = floor[r1][c1];
                r1++;
                r0++;
            }
        }
        else
        {
            while (floor[r0 - 1][c0] == VACANT) // Move container up
            {
                floor[r1][c0] = VACANT;
                floor[r0 - 1][c0] = floor[r0][c0];
                r0--;
                r1--;
            }
        }
    }

    // Return the result of the position of the container
    if (isBlocked == 1)
    {
        if ((floor[r0 - 1][c0] == ENTRY || floor[r1 + 1][c0] == ENTRY))
        {
            return 1;
        }
        else if ((floor[r0 - 1][c0] == EXIT || floor[r1 + 1][c0] == EXIT))
        {
            return 2;
        }
        else if ((floor[r0][c0 - 1] == ENTRY || floor[r0][c1 + 1] == ENTRY))
        {
            return 1;
        }
        else if ((floor[r0][c0 - 1] == EXIT || floor[r0][c1 + 1] == EXIT))
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else if (isBlocked == 0)
    {
        if ((floor[r0 - 1][c0] == ENTRY || floor[r1 + 1][c0] == ENTRY))
        {
            return 1;
        }
        else if ((floor[r0 - 1][c0] == EXIT || floor[r1 + 1][c0] == EXIT))
        {
            return 2;
        }
        else if ((floor[r0][c0 - 1] == ENTRY || floor[r0][c1 + 1] == ENTRY))
        {
            return 1;
        }
        else if ((floor[r0][c0 - 1] == EXIT || floor[r0][c1 + 1] == EXIT))
        {
            return 2;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
    char move;
    printf("\nMove container: ");
    scanf("%c", &move);
    // Ignore non-capital letter inputs
    while ((move < 'A') || (move > 'Z'))
    {
        scanf("%c", &move);
    }
    return move;
}

/* The main Container Yard simulation */
int main(void)
{
    int gameOver = 0;
    int isBlocked = 0;
    int floor[NUM_ROWS][NUM_COLS];
    int rowStart, colStart, rowEnd, colEnd;
    char input;

    /* Print banner */
    printf("............**********************************............\n");
    printf("............* CONTAINER YARD GAME SIMULATION *............\n");
    printf("............**********************************............\n");

    /* Initialise the yard floor grid and add containers */
    InitialiseFloor(floor, 'R', 3);
    AddContainer(floor, 28, 2, 0);
    AddContainer(floor, 11, 3, 1);
    AddContainer(floor, 41, 2, 1);
    AddContainer(floor, 42, 2, 1);
    AddContainer(floor, 42, 2, 1);
    AddContainer(floor, 34, 2, 0);
    AddContainer(floor, 36, 3, 1);
    AddContainer(floor, 37, 2, 1);
    AddContainer(floor, 53, 2, 0);
    AddContainer(floor, 30, 2, 1);

    /* Print status */
    printf("ENGGEN131 2021 - C Project\nContainer Yard!  The containers are rushing in!\n");
    printf("In fact, %.2f%% of the yard floor is available for containers!\n\n", FloorAreaAvailable(floor, 20.5, 10.3));

    /* Main simulation loop */
    while (gameOver != 2)
    {
        PrintFloor(floor);
        input = GetMove();
        isBlocked = LocateContainer(floor, input, &rowStart, &colStart, &rowEnd, &colEnd);
        gameOver = MoveContainer(floor, rowStart, colStart, rowEnd, colEnd, isBlocked);
    }

    /* A container is ready to exit - the simulation is over */
    PrintFloor(floor);
    printf("\nCongratulations, you've succeeded!");

    return 0;
}
