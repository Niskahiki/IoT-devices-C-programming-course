/*
Write a function named read_positive. The function takes a pointer to int as a parameter and
returns a bool.
bool read_positive(int *value);

The function asks (=prints) user to enter a positive number. If user enters a valid number and the
number is positive the function stores the number using the pointer and returns true. If reading
number fails or number is not positive function returns false without making changes to the value
using pointer.

Write a program that “plays” a guessing game with user. The program asks user to guess how much
money it has and after the guess claims to twice as much plus 20 euros. Program must use the
function above to ask user to enter the number. If reading fails, function returns false, program asks
to enter a number again. Program stops when user has entered an incorrect value three times.
*/

#include <stdio.h>
#include <stdbool.h>

bool read_positive(int *value);

int main(void) {

    int incorrectInputCounter = 0;

    while(incorrectInputCounter < 3) {
        int value = 0;

        bool gotPositiveNumber = read_positive(&value);

        if (gotPositiveNumber) {
            int moneyInPocket = (value * 2) + 20;

            printf("You didn't get it right. I have %d euros.\n", moneyInPocket);

        } else {
            
            incorrectInputCounter += 1;
        }
    }

    printf("I give up! See you later!\n");

    return 0;
}

bool read_positive(int *value) {

    printf("Guess how much money I have!\n");

    printf("Enter a positive number: ");
    if (scanf("%d", value) != 1) {
        while(getchar() != '\n');
        printf("Incorrect input.\n");
    } else {
        if (0 > *value) {
            printf("Incorrect input. Value must be positive number.\n");
        } else {
            return true;
        }
    }

    return false;
}