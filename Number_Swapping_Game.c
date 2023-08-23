#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void createMatrix(int arr[][4])
{
    // 4 x 4 Matrix
    int n = 15;
    int num[n], i, j;
    for (i = 0; i < 15; i++)
        num[i] = i + 1;

    srand(time(NULL)); // Generating random number.

    int lastIndex = n - 1, index;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            if (lastIndex >= 0)
            {
                index = rand() % (lastIndex + 1); // -> performing % operation by lastIndex+1
                arr[i][j] = num[index];           // will give index , so put that num[index] number in matrix
                num[index] = num[lastIndex--];    // and replace last number with this indexed positioned number
            }                                     // and finally lastIndex--
        }
    arr[i - 1][j - 1] = 0; // last number zero
}
void showMatrix(int arr[][4])
{
    int i, j;
    printf("--------------------\n");
    for (i = 0; i < 4; i++)
    {
        printf("|");
        for (j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                printf("%2d | ", arr[i][j]);
            else
                printf("   | ");
        }
        printf("\n");
    }

    printf("--------------------\n");
}
int winner(int arr[][4])
{
    int i, j, k = 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++, k++)
            if (arr[i][j] != k && k != 16)
                break;
        if (j < 4)
            break;
    }

    if (j < 4)
        return 0;
    return 1;
}
void swap(int *x, int *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
    printf("");
}

// Reads the user input character and return ascii value of that
int readEnteredKey()
{
    char c;
    c = getch();
    if (c == -32)
        c = _getch();

    return c;
}

// shift up function
int shiftUp(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 3) // shifting not possible
        return 0;

    // Successfully swapped two numbers !
    swap(&arr[i][j], &arr[i + 1][j]);
    return 1; // Success
}

int shiftDown(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 0) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i - 1][j]); // swap numbers

    return 1; // shift up success
}

int shiftRight(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (j == 0) // shifting not possible
        return 0;

    swap(&arr[i][j], &arr[i][j - 1]);

    return 1; // shift up success
}

int shiftLeft(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }

    if (j == 3) // shifting not possible
        return 0;

    swap(&arr[i][j], &arr[i][j + 1]);
    return 1; // shift up success
}

// Game rules
void gameRule(int arr[][4])
{
    system("cls");

    int i, j, k = 1;

    printf("\t\t  MATRIX PUZZLE\n");
    printf("\n");
    printf(RED "                 RULE OF THIS GAME                 \n" RESET);
    printf(RED "\n1.You can move only 1 step at a time by arrow key " RESET);
    printf(YELLOW "\n\tMove Up   : by Up arrow key " RESET);
    printf(YELLOW "\n\tMove Down : by Down arrow key" RESET);
    printf(YELLOW "\n\tMove Left : by Left arrow key" RESET);
    printf(YELLOW "\n\tMove Right: by Right arrow key" RESET);

    printf(RED "\n2.You can move number at empty position only " RESET);
    printf("\n");
    printf(RED "\n3. For each valid move : your total number of move will decreased by 1 \n" RESET);
    printf(RED "4. Wining situation : " RESET);
    printf(RED " Number in a 4*4 matrix should be in order from 1 to 15 " RESET);
    printf("\n\n            winning situation:         \n");

    printf(CYAN"---------------------\n" RESET);

    for (i = 0; i < 4; i++)
    {
        printf(CYAN "| " RESET);
        for (j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                printf(CYAN "%2d | " RESET, 4 * i + j + 1);
            else
                printf(CYAN "   |" RESET);
        }
        printf("\n");
    }

    printf(CYAN "---------------------\n" RESET);
    printf("\n5.You can exit the game at any time by pressing 'E' or 'e' ");

    printf("\nSo Try to win in minimum no of move \n");

    printf("\nEnter any key to start.....   ");

    int x = readEnteredKey();
}

int main()
{
    int arr[4][4];   
    int maxTry = 50;
    char name[20];
    for (int k = 0; k < 3; k++)
        printf("\n");
    printf("Player Name: ");
    scanf("%s", name);

    system("cls"); 

    while (1)
    {
        createMatrix(arr); // calling function to create  matrix
        gameRule(arr);     // game rule function calling

        while (!winner(arr)) // checking for winning situation
        {
            system("cls");
            if (!maxTry) // for remaining zero move
                break;

            printf("\n\n  Player Name:  %s ,  Move remaining : %d\n\n", name, maxTry);

            showMatrix(arr); // show matrix

            int key = readEnteredKey(); // this will return ascii code of user entered key

            switch (key) // maping
            {
            case 101: // ascii of E

            case 69: // ascii of e
                printf("\a\a\a\a\a\a\n     Thanks for Playing ! \n\a");
                printf("\nHit 'Enter' to exit the game \n");
                key = readEnteredKey();
                return 0;

            case 72: // arrow up
                if (shiftUp(arr))
                    maxTry--;
                break;
            case 80: // arrow down
                if (shiftDown(arr))
                    maxTry--;
                break;
            case 77: // arrow  right
                if (shiftRight(arr))
                    maxTry--;
                break;
            case 75: // arrow left
                if (shiftLeft(arr))
                    maxTry--;
                break;
            default:

                printf("\n\n      \a\a Not Allowed \a");
            }

        }

        if (!maxTry)
            printf(RED "\n\a          YOU LOSE !          \a\a\n" RESET);
        else
            printf( GREEN "\n\a!!!!!!!!!!!!!Congratulations  %s for winning this game !!!!!!!!!!!!!\n\a" RESET, name);

        fflush(stdin); // Will clear the buffer
        char check;
        printf(GREEN "\nWant to play again ? \n" RESET);
        printf("enter 'y' to play again:  ");
        scanf("%c", &check);

        // Leave the game here itself !
        if ((check != 'y') && (check != 'Y'))
            break;

        maxTry = 4;
    }
    return 0;
}