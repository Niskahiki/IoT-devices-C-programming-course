/*
Write a program that asks user to enter a filename. Then program tries to open the file in textmode
for reading. If opening the file fails the program prints an error message with the filename to stderr
and then exits. If the file is opened the program starts reading integers from the file until reading
fails or the file ends. When reading stops the program prints the count of numbers and the lowest
and highest number that was read from the file. Then program closes the file.

For testing make a few text files with integers using your favourite text editor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FILENAME_MAX_SIZE 256
#define LINE_SIZE 80

void ask_user_for_file_name(char *fileName, int fileName_max_size);
void compare_and_update_numbers(int *value, int *min, int *high);
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
    
    char line[LINE_SIZE];
    int value = 0;
    int highest_number = INT_MIN; // Every number will be higher
    int lowest_number = INT_MAX; // Every number will be smaller
    int number_count = 0;

    while(fgets(line, LINE_SIZE, file) != NULL) {
        if (sscanf(line, "%d", &value) == 1) {
            compare_and_update_numbers(&value, &lowest_number, &highest_number);
            number_count++;
        }
    }

    fclose(file);

    if (number_count == 0) {
        printf("\nNo numbers found from file: %s", fileName);
    } else {
        printf("\nRead %d numbers from %s\n", number_count, fileName);
        printf("Lowest number was: %d. Highest number was: %d", lowest_number, highest_number);
    }

    return 0;
}

void ask_user_for_file_name(char *fileName, int fileName_max_size) {
    printf("Enter filename to open: ");
    read_user_input(fileName, fileName_max_size);
    remove_new_line_from_string(fileName);
}

void compare_and_update_numbers(int *value, int *min, int *high) {
    if (*value > *high) {
        *high = *value;
    }

    if (*value < *min) {
        *min = *value;
    }
}

void read_user_input(char *string, int string_size) {
    if (fgets(string, string_size, stdin) == NULL) {
        string[0] = '\0';
    }
}

void remove_new_line_from_string(char *string) {
    if (string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
}