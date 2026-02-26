/*
Write a program that reads lines of text in to an array of strings. The maximum length of the line is
80 characters and the maximum number of lines is 100.

The program asks user to enter a filename. Then program tries to open the file in textmode for
reading. If opening the file fails the program prints an error message with the filename to stderr and
then exits. The program reads lines from the file into the array until the file ends or the array is full
(100 lines read). Then program closes the file.

Then program converts all letters to upper case (see toupper() – function).

Then program opens the file for writing in text mode and writes all read lines to file and closes the
file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME_MAX_SIZE 256
#define MAX_LINE_LENGTH 80
#define MAX_NUMBER_OF_LINES_IN_FILE 100

void ask_user_for_file_name(char *fileName, int fileName_max_size);
void upper_case_everything(char array[][MAX_LINE_LENGTH], int last_index);
void read_user_input(char *string, int string_size);
void remove_new_line_from_string(char *string);

int main(void) {

    char fileName[FILENAME_MAX_SIZE];

    ask_user_for_file_name(fileName, FILENAME_MAX_SIZE);

    FILE *file;

    file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s", fileName);
        exit(1);
    }

    char lines[MAX_NUMBER_OF_LINES_IN_FILE][MAX_LINE_LENGTH];
    int line_count = 0;

    while(line_count < MAX_NUMBER_OF_LINES_IN_FILE &&
        fgets(lines[line_count], MAX_LINE_LENGTH, file) != NULL) {
        line_count++;
    }

    fclose(file);

    upper_case_everything(lines, line_count);

    file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s for write.", fileName);
        exit(1);
    }

    for (int i = 0; i <= line_count; i++) {
        fputs(lines[i], file);
    }

    fclose(file);

    return 0;
}

void ask_user_for_file_name(char *fileName, int fileName_max_size) {
    printf("Enter filename to open: ");
    read_user_input(fileName, fileName_max_size);
    remove_new_line_from_string(fileName);
}

void upper_case_everything(char array[][MAX_LINE_LENGTH], int last_index) {
    for (int i = 0; i <= last_index; i++) {
        for (int j = 0; array[i][j] != '\0'; j++) {
            array[i][j] = toupper(array[i][j]);
        }
    }
}

void read_user_input(char *string, int string_size) {
    if(fgets(string, string_size, stdin) == NULL) {
        string[0] = '\0';
    }
}

void remove_new_line_from_string(char *string) {
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}