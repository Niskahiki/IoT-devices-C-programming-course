/*
    Write a program that asks user to enter a file name. Program opens the file in text mode. The file is
    supposed to contain NMEA (GPS) data. Program looks for lines that start with ‘$’ and have an
    asterisk ‘*’ later on the line. If a line meeting the condition is found the program verifies the
    checksum of the line. If checksum is ok line is printed prefixed with [ OK ] otherwise line is
    prefixed with [FAIL].
    Checksum is calculated by XORing all characters after ‘$’ and before ‘*’. The result is checked against
    the two-digit hexadecimal value that follows ‘*’. If they are equal line is ok.
    For example:
        $GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76
        $GPGSA,A,3,10,07,05,02,29,04,08,13,,NOT,OK,,1.72,1.03,1.38*0A
        $GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70
        $GPGSV,3,2,11,02,39,223,19,13,28,070,17,26,23,252,,04,14,186,14*79
        $GPGSV,3,3,11,29,09,301,24,16,09,020,,36,,,*76
        $GPRMC,092750.000,A,5321.6802,N,00630.3372,W,0.02,31.66,280511,,,A*43
        $GPGGA,092751.000,5321.6802,N,00630.3371,W,1,8,1.03,61.7,M,55.3,M,,*75
        $GPGSA,A,3,10,07,05,02,29,04,08,13,BAD,,,,1.72,1.03,1.38*0A
        $GPGSV,3,1,11,10,63,137,17,07,61,098,15,05,59,290,20,08,54,157,30*70
        $GPGSV,3,2,11,02,39,223,16,13,28,070,17,26,23,252,,04,14,186,15*77
        $GPGSV,3,3,11,29,09,301,24,16,09,020,BROKEN,36,,,*76
        $GPRMC,092751.000,A,5321.6802,N,00630.3371,W,0.06,31.66,280511,,,A*45
    Above the lines that read “NOT,OK”, “BAD” and “BROKEN” have a failing checksum.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRING_SIZE 256
#define EXPECTED_LINE_MAX_SIZE 200

void ask_user_for_file_name(char *file_name, int file_name_max_size);
FILE *open_file(char *file_name);

void check_NMEA(FILE *file, int expected_line_max_size);

void print_invalid_line(char *line);
void print_valid_line(char *line);

void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);

int main(void) {

    char file_name[STRING_SIZE];
    ask_user_for_file_name(file_name, STRING_SIZE);

    FILE *file = open_file(file_name);

    check_NMEA(file, EXPECTED_LINE_MAX_SIZE);

    fclose(file);

    return 0;
}

void ask_user_for_file_name(char *file_name, int file_name_max_size) {
    printf("Enter filename to open: ");
    read_input(file_name, file_name_max_size);
    remove_trailing_whitespace(file_name);
}

FILE *open_file(char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s\n", file_name);
        exit(1);
    }

    return file;
}

void check_NMEA(FILE *file, int expected_line_max_size) {
    char current_line[expected_line_max_size];

    while (fgets(current_line, expected_line_max_size, file)) {   
        remove_trailing_whitespace(current_line);

        if (current_line[0] != '$') { // Check that the line starts with '$'
            print_invalid_line(current_line);

        } else {
            char *asterisk = strchr(current_line, '*'); // Search line for the asterisk

            if (asterisk == NULL) { // Not found
                print_invalid_line(current_line);

            } else {

                int calculated_checksum = 0;

                for (char *character = current_line + 1; character < asterisk; character++) { // +1 to hop over the '$'
                    calculated_checksum ^= *character; // XOR the character to checksum
                }

                int expected_checksum = strtol(asterisk + 1, NULL, 16); // 16 (hexadecimal) because the NMA checksum is 16bit hexadecimal

                if (calculated_checksum == expected_checksum) {
                    print_valid_line(current_line);
                } else {
                    print_invalid_line(current_line);
                }

            }
        }
    }
}

void print_invalid_line(char *line) {
    printf("[ FAIL ] %s\n", line);
}

void print_valid_line(char *line) {
    printf("[ OK ] %s\n", line);
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
