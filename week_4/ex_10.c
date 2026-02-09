/*
Write a program that asks user to enter a string. Program must use fgets to read user input and
remove the linefeed at the end of the string. Then program prints the length of the string and checks
if the string is “stop”. If it is the program stops else program asks user to enter a new string (and
prints the length etc.).
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 256

void read_user_input(char *text, int string_size);
void remove_new_line_from_string(char *string);

int main(void) {
    char text[STRING_SIZE];

    bool continue_asking = true;

    while (continue_asking) {
        read_user_input(text, STRING_SIZE);
    
        remove_new_line_from_string(text);

        if (strcmp(text, "stop") == 0) {
            continue_asking = false;
        } else {
            printf("\nString lenght is: %d.\n", strlen(text));
        }
    }

    return 1;
}

void read_user_input(char *text, int string_size) {
    printf("\nEnter a string or 'stop' to stop: ");
    if (fgets(text, string_size, stdin) == NULL) {
        text[0] = '\0';
    }
}

void remove_new_line_from_string(char *string) {
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}