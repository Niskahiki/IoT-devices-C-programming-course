/*
Write a password generator function that takes three parameters: character pointer, integer (size of
the array), a const char pointer (a word) and returns a bool. The function generates password and
stores it in the array and returns true. The length of the generated password is the
𝑙𝑒𝑛𝑔𝑡ℎ 𝑜𝑓 𝑤𝑜𝑟𝑑 × 2 + 1 characters. If the password does not fit in the string function returns false
and does not modify the string.

The password must contain the word given as a parameter so that password starts with a random
printable character and every other letter is a letter from the word and every other is a random
printable character. The password ends with a random printable character. Note that printable
characters are not limited to alphanumerical characters.

Write a program that asks user to enter a word to place in the password or to enter “stop” to stop
the program. The size of the string to read the word into must be 32. If user does not enter stop the
program generates a password using the generator function. If a password is generated successfully
the program prints it otherwise an error message is printed. Then the program asks for another
word.

For example:
User enters: metropolia
Program prints: #m%eGtqrHo&p2o+lBimaY

You don’t need to use colours. They are just a visual aid. The random characters will naturally be
different on your program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define STRING_SIZE 32
#define PASSWORD_MAX_SIZE 32

void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);
char generate_random_char();
bool password_generator(char *password, int password_max_size, const char *word);


int main(void) {

    bool continue_asking = true;
    char word[STRING_SIZE];
    char generated_password[PASSWORD_MAX_SIZE];

    srand(time(NULL)); // Seed for random

    while (continue_asking) {
        printf("\nEnter word for password generation or \"stop\" to stop: ");
        read_input(word, STRING_SIZE);
        remove_trailing_whitespace(word);

        if (word[0] == '\0') {
            printf("\nInvalid Input!\n");
        } else {

            if (strcmp(word, "stop") == 0) {
                continue_asking = false;
            } else {
                if (password_generator(generated_password, PASSWORD_MAX_SIZE, word)) {
                    printf("\nYour generated password: %s", generated_password);
                } else {
                    printf("\nThe given word doesn't fit in to the password.\n");
                }
            }
        }
    }
    
    return 0;
}

bool password_generator(char *password, int password_max_size, const char *word) {
    int word_length = strlen(word);
    int required_size_for_password = word_length * 2 + 2; // We need one for the first generated number and one for '\0'

    if (password_max_size < required_size_for_password) {
        return false;
    }

    for (int i = 0; i < (required_size_for_password - 1); i++) {
        if ((i % 2) == 0) { // every even char index on the password should be generated
            password[i] = generate_random_char();
        } else { // every odd char index on the password should be original from the word
            password[i] = word[i/2]; // 1 / 2 = 0; 3 / 2 = 1
        }
    }

    password[required_size_for_password - 1] = '\0';

    return true;
}

char generate_random_char() {
    int first_char_in_ascii = 33;
    int last_char_in_ascii = 126;

    int random_char_as_integer = (rand() % (last_char_in_ascii - first_char_in_ascii + 1)) + first_char_in_ascii;
    return random_char_as_integer;
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