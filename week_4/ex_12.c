/*
Write a function count_words that takes two strings as a parameter and returns an integer. The
function counts the number of times the second string occurs in the first string and returns the
count. Use strstr() from standard library to find the strings. Note that if the string is found you need
to advance past the current occurrence before searching again. Hint: use a pointer to the string and
use pointer arithmetic to advance it past the current match.

Prototype of the function:
int count_words(const char* str, const char *word);

Write a program that asks user to enter a string and a word. Then program calls count_words and
prints the return value. If the word was “stop” the program stops otherwise it asks user to enter a
string and a word again.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 256

int count_words(const char *str, const char *word);
void read_user_input(char *string, int string_size);
void remove_new_line_from_string(char *string);

int main(void) {

    char string[STRING_SIZE];
    char word[STRING_SIZE];
    bool continue_asking_for_words = true;

    while (continue_asking_for_words) {

        printf("Enter string of text or \"stop\" to stop: ");
        read_user_input(string, STRING_SIZE);
        remove_new_line_from_string(string);

        if (strcmp(string, "stop") == 0) {
            continue_asking_for_words = false;

        } else {

            printf("Enter a word to search for: ");
            read_user_input(word, STRING_SIZE);
            remove_new_line_from_string(word);

            if (string[0] == '\0') {
                printf("\nString can't be empty.\n");

            } else if (word[0] == '\0') {
                printf("\nWord to search for can't be empty.\n");

            } else {

                int times_found_in_string = count_words(string, word);

                printf("\nThe word \"%s\" exists %d time(s) in the given string.\n", word, times_found_in_string);
            }
        }
    }


    return 1;
}

int count_words(const char *str, const char *word) {

    int word_size = strlen(word);
    int times_found_in_string = 0;
    bool continue_search = true;

    do {
        str = strstr(str, word); // Update the pointer to point where the word's first character is found.

        if (str == NULL) { // Word is not found in the string
            continue_search = false;

        } else {
            str += word_size; // Pointer Arithmetic || Pointer hops the size of the word forward. 1 char = 1 byte. Pointer hops 1byte * n forward.
            times_found_in_string++;

        }

    } while (continue_search);

    return times_found_in_string;
}

void read_user_input(char *string, int string_size) {
    if (fgets(string, string_size, stdin) == NULL) {
        string[0] = '\0';
    }
}

void remove_new_line_from_string(char *string) {
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}
