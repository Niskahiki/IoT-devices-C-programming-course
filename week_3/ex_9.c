/*
Write a function called find_first that takes two parameters: pointer to constant unsigned integers
and an unsigned integer to find and returns an integer.

int find_first(const unsigned int *array, unsigned int what);

The function searches for the given number in the array until it is found or the current number in the
array is zero. If the number is not found until a zero is seen the program returns -1. If the number is
found function returns the index at which the number was found. Note that we don’t pass the size of
the array as a parameter but we use zero as an end marker to stop at the end of the array.

Write a program that defines an array of 20 integers and fills the first 19 elements with random
numbers in range 1 - 20 and puts a zero as the last number in the array. The program prints the array
one number per line.

Program then asks user to enter number to search for or zero to stop. If the number is not zero
program calls find_first to see if the number occurs in the array. If the number is found it prints the
index where the number is found or “not found”. If user enters zero, the program stops otherwise
program asks again user to enter a number to find.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ARRAY_SIZE 20
#define RANDOM_MAX 20

int get_random_unsigned_number_in_range(int max);
void print_array_one_item_per_row(const unsigned int *array, const int array_size);
int ask_user_for_unsigned_integer(void);
int find_first(const unsigned int *array, unsigned int what);

int main(void) {
    srand(time(NULL));
    int number_array[ARRAY_SIZE];

    for (int i = 0; i < (ARRAY_SIZE - 1); i++) {
        number_array[i] = get_random_unsigned_number_in_range(RANDOM_MAX);
    }

    number_array[(RANDOM_MAX - 1)] = 0;

    print_array_one_item_per_row(number_array, ARRAY_SIZE);

    bool continue_asking = true;
    while (continue_asking) {
        int user_number = ask_user_for_unsigned_integer();

        if (user_number == 0) {
            return 1;
        }

        int number_found_at = find_first(number_array, user_number);

        if (number_found_at == -1) {
            printf("Number not found.\n");
        } else {
            printf("Number (%d) found at index: %d\n", user_number, number_found_at);
        }
    }

    return 1;
}

int get_random_unsigned_number_in_range(int max) {
    return 1 + rand() % max;
}

void print_array_one_item_per_row(const unsigned int *array, const int array_size) {
    for (int i = 0; i < array_size; i++) {
        printf("%d\n", array[i]);
    }
}

int ask_user_for_unsigned_integer(void) {
    bool hasUnsignedInteger = 0;
    int userNumber = -1;

    while (!hasUnsignedInteger) {
        printf("\nEnter unsigned number to search for or 0 to stop: ");
        if (scanf("%d", &userNumber) != 1) {
            while(getchar() != '\n');
            printf("Invalid input.\n");

        } else {

            if (userNumber < 0) {
                printf("Invalid input. Enter unsigned number.\n");

            } else {
                return userNumber;
            }
        }
    }
}

int find_first(const unsigned int *array, unsigned int what) {
    int k = 0;
    bool has_found_given_number_or_zero = false;

    while(!has_found_given_number_or_zero) {
        if (array[k] == what) {
            return k;
        }

        if (array[k] == 0) {
            return -1;
        }

        k++;
    }
}
