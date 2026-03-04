/*
Write a program that asks user to enter a number in the range from 0 to 15 or a negative number to
stop. If user enters a number between 0 and 15 the program generates a random number and prints
it in hexadecimal. Then program shifts the number to the right by the amount user entered and uses
bitwise and to clear all other bits except bits 0-5 and prints the result in hexadecimal with two digits
and leading zeros.

Note: bit numbering starts from 0
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define INPUT_MAX_SIZE 10

void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);
bool convert_string_to_int(char *string, int *number);

int main(void) {

    bool continue_asking = true;
    char input_string[INPUT_MAX_SIZE];
    int user_number = 0;
    unsigned int random_number = 0;
    unsigned int sifted = 0;
    unsigned int result = 0;

    unsigned int mask = (1 << 6) - 1; // (1 << 6) == 1000000 | (1000000) -1 == 0111111 

    srand(time(NULL)); // Seed for random

    while (continue_asking) {
        printf("\nEnter number between 0 and 15, or enter negative number to stop: ");
        read_input(input_string, INPUT_MAX_SIZE);
        remove_trailing_whitespace(input_string);

        if (convert_string_to_int(input_string, &user_number)) {
            if (user_number < 0) {
                continue_asking = false;
            } else if (user_number >= 0 && user_number <= 15) {
                random_number = rand();

                printf("\nRandom number (%d) as hex: %x\n", random_number, random_number);

                sifted = random_number >> user_number; // Bitwise. Sift numbers right the amount of user number (0 - 15)
                result = sifted & mask; // Keep last 6 bits. For example 11111001 & 00111111 would be 00111001

                printf("Sifted and masked result as hex is: %02x\n", result);
            } else {
                printf("\nInvalid Input!\n");
            }
        } else {
            printf("\nInvalid Input!\n");
        }
    }
    

    return 0;
}

void clear_buffer(char *buffer) {
    if (buffer[strlen(buffer) - 1] != '\n') {
        int c;
        while((c = getchar()) != '\n' && c != EOF);
    }
}

void read_input(char *str, int max_input_size) {
    if (fgets(str, max_input_size, stdin) != NULL) {
        clear_buffer(str);
    }
}

void remove_trailing_whitespace(char *string) {
    if (string == NULL) return;

    int len = strlen(string);
    if (len == 0) return;

    int i = len - 1;

    while (i >= 0 && isspace((unsigned char) string[i])) {
        string[i] = '\0'; // Replace trailing whitespace characters with '\0'
        i--; 
    }
}

bool convert_string_to_int(char *string, int *number) {
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    char *end;
    long value = strtol(string, &end, 10); // 10 means base 10 numbers

    if (*end != '\0') {
        return false;
    }

    *number = (int)value;

    return true;
}