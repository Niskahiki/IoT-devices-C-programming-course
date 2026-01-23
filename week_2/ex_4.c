/*
Write a function called read_integer that takes no parameters and returns an integer. The function
reads a single integer. If the reading fails the function prints “invalid input” and tries to read an
integer again. When an integer is successfully read the function returns the integer.
The declaration of the function is:
int read_integer(void);
Write a program that asks user to enter positive integers or a negative number to stop. The program
must use read_integer-function to read the number. The program calculates and prints the average
of the entered numbers excluding the negative number. For example, if user enters: 1 3 4 2
7 -1, the program prints 3.4 as the average.
The program must print the average with three decimal precision. 
*/

#include <stdio.h>
int read_integer(void);


int main(void) {
    int currentNumber = 0;
    int sumOfNumbers = 0;
    int countOfNumbers = 0;
    do {
        currentNumber = read_integer();

        if (currentNumber >= 0) {
            sumOfNumbers += currentNumber;
            countOfNumbers++;
        }
    } while (currentNumber >= 0);

    float avg = 0;

    if (sumOfNumbers != 0) {
        avg = (float)sumOfNumbers / countOfNumbers;
    }

    printf("\nYou entered %d positive numbers. The avarage is: %.3f", countOfNumbers, avg);

    return 0;
}


int read_integer(void) {
    int hasNumber = 0;
    while (!hasNumber) {
        int number = 0;
        printf("\nEnter positive numbers or negative to stop: ");
        if (scanf("%d", &number) != 1) {
            while(getchar() != '\n');
            printf("Invalid input.\n");
        } else {
            return number;
        }
    }
}