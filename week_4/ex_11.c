/*
Write a function called replace_char that takes two strings as parameters and returns an integer.
The first string is the string to modify and the second is a string containing two characters. The
function finds every occurrence of the first character of the second string and replaces them with
the second character. For example:

char text[80] = “I am so tired of Python. C is much better language”;
count = replace_char(test, “e3”);

The call above will find every occurrence of ‘e’ and replace it with ‘3’.

Prototype of the function:
int replace_char(char *str, const char *repl);

The function returns the number of characters replaced. The return value can be zero if no
characters were found or if the second string does not contain two characters.

Write a program that asks user to enter both strings and then calls replace_char. The program prints
both return value and the modified string if the return value is greater than zero. If the return value
is zero program prints “String was not modified”.
*/

#include <stdio.h>
#include <string.h>

#define STRING_SIZE 256
#define REPL_SIZE 3

void read_user_input(char *string, int string_size);
int replace_char(char *str, const char *repl);
void remove_new_line_from_string(char *string);

int main(void) {
    char text[STRING_SIZE];
    char repl[REPL_SIZE];

    printf("Enter text: ");
    read_user_input(text, STRING_SIZE);


    printf("\nEnter replacement characters. First char is what to look for and second character is replace with: ");
    read_user_input(repl, REPL_SIZE);

    remove_new_line_from_string(text);
    remove_new_line_from_string(repl);
    
    const int count_of_replacements = replace_char(text, repl);

    if (count_of_replacements == 0) {
        printf("\nString was not modified.\n");
    } else {
        printf("\nAmount of replacements: %d\n", count_of_replacements);
        printf("Modified string: %s", text);
    }

    return 1;
}

void read_user_input(char *string, int string_size) {
    if (fgets(string, string_size, stdin) == NULL) {
        string[0] == '\0';
    }
}

int replace_char(char *str, const char *repl) {
    if (repl[1] == '\0') {
        return 0;
    }

    int amount_of_changes = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == repl[0]) {
            str[i] = repl[1];
            amount_of_changes++;
        }
    }

    return amount_of_changes;
}

void remove_new_line_from_string(char *string) {
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}