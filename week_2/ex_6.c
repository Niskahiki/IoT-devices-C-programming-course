/*
Write a program that prints a menu and asks user to select an operation. The operations are:
• Roll D6
• Roll D10
• Quit

Input must be validated and a descriptive error message must be printed if input is invalid. Rolling
D6 prints a random number in the range of 1 – 6 and rolling D10 prints a random number in the
range of 1 – 10. If user does not select quit the program prints the menu again.

Use functions to structure your program
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// D6 dice max
#define D6Max 6

// D10 dice max 
#define D10Max 10

void printMenu(void);
int readMenuSelect(void);
int rollADice(int max);

int main(void) {
    srand(time(NULL));

    int userWantToQuit = 0;
    do {
        printMenu();

        switch(readMenuSelect()) {
            case 1:
                printf("Rolling a D6 dice.\nYou got: %d\n", rollADice(D6Max));
                break;
            case 2:
                printf("Rolling a D10 dice.\nYou got: %d\n", rollADice(D10Max));
                break;
            case 3:
                printf("Quiting...\nBye!\n");
                userWantToQuit = 1;
                break;
            default:
                printf("Invalid menu selection.");
                break;
        }

    } while (!userWantToQuit);
    
    return 0;
}

void printMenu(void) {
    printf("\nMenu:\n");
    printf("[1]\tRoll D6\n[2]\tRoll D10\n[3]\tQuit\n");
}

int readMenuSelect(void) {
    int hasANumber = 0;
    while (!hasANumber) {
        int number = 0;

        printf("\nSelect: ");
        if(scanf("%d", &number) != 1) {
            while(getchar() != '\n');
            printf("Invalid input. You must enter a number.");

        } else {
            return number;
        }
    }
}

int rollADice(int max) {
    return rand() % max + 1;
}