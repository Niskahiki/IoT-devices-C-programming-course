/*
    Implement a program that consists of three files: main.c, debug.c and debug.h.
    Debug.c contains two functions:
    • set_debug_level
    • dprintf

    Set_debug_level takes one integer parameter (debug level) and stores the value in a static variable
    that is accessible to all functions in the file but not globally.

        void set_debug_level(int debug_level);

    Dprintf works like printf but there is an extra integer parameter (debug level) that comes before the
    usual printf parameters:

        int dprintf(int debug_level, const char *fmt, …);

    If dprintf debug level is lower or equal to the stored debug level then function prints the output to
    stderr prefixed with [DBGx] , where x is the debug level given as parameter. Otherwise, function
    prints nothing and returns zero.

    Write a program that asks user to enter debug level in range 0 – 4 and calls set_debug_level with the
    number. Then program prints five messages with a random debug level in range 0 – 4 using dprintf.
    Get a new random debug level for each message. The messages must have at least one numerical
    argument that is a running index that starts from one. First message has index 1,second message 2,
    etc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "debug.h"

#define INPUT_SIZE 2
#define DEBUG_LEVEL_MAX 4
#define DEBUG_LEVEL_MIN 0

int convert_string_to_int(char *string);
void print_invalid_input();
void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);
void test_debug();
int get_random_debug_level(int min, int max);

int main(void) {
    bool has_valid_debug_level = false;
    char input_str[INPUT_SIZE];
    int debug_level;

    while (!has_valid_debug_level) {
        printf("\nEnter debug level (0 - 4): ");
        read_input(input_str, INPUT_SIZE);
        remove_trailing_whitespace(input_str);

        debug_level = convert_string_to_int(input_str);

        if (debug_level == -1) {
            print_invalid_input();
        } else {
            if (debug_level >= DEBUG_LEVEL_MIN && debug_level <= DEBUG_LEVEL_MAX) {
                has_valid_debug_level = true;
            } else {
                print_invalid_input();
            }
        }
    }

    set_debug_level(debug_level);

    srand(time(NULL));

    test_debug();

    return 0;
}

int convert_string_to_int(char *string) {
    if (string == NULL || string[0] == '\0') {
        return -1;
    }

    char *end;
    long value = strtol(string, &end, 10);

    if (*end != '\0') {
        return -1;
    }

    return (int) value;
}

void test_debug() {
    for (int i = 1; i <= 5; i++) {
        dprintf(get_random_debug_level(DEBUG_LEVEL_MIN, DEBUG_LEVEL_MAX), "%d: I love C!\n", i);
    }
}

int get_random_debug_level(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void print_invalid_input() {
    printf("\nInvalid Input!\n");
}

void clear_buffer(char *buffer) {
    if(buffer[strlen(buffer) - 1] != '\n') {
        int c;
        while((c = getchar()) != '\n' && c != EOF);
    }
}

void read_input(char *str, int max_input_size) {
    if(fgets(str, max_input_size, stdin) != NULL) {
        clear_buffer(str);
    }
}

void remove_trailing_whitespace(char *string) {
    if (string == NULL) return;

    int len = strlen(string);
    if (len == 0) return;

    int i = len - 1;

    while (i >= 0 && isspace((unsigned char) string[i])) {
        string[i] = '\0';
        i--;
    }
}