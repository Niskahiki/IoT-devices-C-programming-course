/*
Write a program that reads data from a text file into an array of structures. The size of the array is 40
elements.

The structure is defined as:
typedef struct menu_item_ {
  char name[50];
  double price;
} menu_item;

The program asks user to enter a filename. Then program tries to open the file in textmode for
reading. If opening the file fails the program prints an error message with the filename to stderr and
then exits.

Program reads data from the text file into the array until end of file or the array is full. Each row of
the file contains data of one structure. The members are separated by semicolons. For example:
Mega double burger with bacon and cheese; 23.50
Belgian style fries with vegan mayo; 5.60

When reading ends the program closes the file and prints the content of the array in formatted
columns. Price is printed into a field of eight characters with two decimals precision followed by the
name of the item. Unused elements are not printed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 40
#define STRING_SIZE 256
#define LINE_MAX_LENGTH 60

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

void ask_user_for_file_name(char *fileName, int fileName_max_size);
int read_file_lines_to_array(char array[][LINE_MAX_LENGTH], FILE *file, int max_amount_of_lines, int max_line_length);
int validate_and_build_menu_array_items(char array[][LINE_MAX_LENGTH], menu_item *menu_array, int array_size);
void validate_and_get_menu_item_price(char *string, double *price);
void print_out_menu_items(menu_item *array, int array_size);
void read_user_input(char *string, int string_size);
void remove_new_line_from_string(char *string);


int main(void) {
    
    char fileName[STRING_SIZE];

    ask_user_for_file_name(fileName, STRING_SIZE);

    FILE *file;

    file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s", fileName);
        exit(1);
    }

    char lines[ARRAY_SIZE][LINE_MAX_LENGTH];
    int array_size = read_file_lines_to_array(lines, file, ARRAY_SIZE, LINE_MAX_LENGTH);

    menu_item menu_array[ARRAY_SIZE];
    int menu_array_size = validate_and_build_menu_array_items(lines, menu_array, array_size);

    print_out_menu_items(menu_array, menu_array_size);

    return 0;
}

void ask_user_for_file_name(char *fileName, int fileName_max_size) {
    printf("Enter filename to open: ");
    read_user_input(fileName, fileName_max_size);
    remove_new_line_from_string(fileName);
}

int read_file_lines_to_array(char array[][LINE_MAX_LENGTH], FILE *file,
    int max_amount_of_lines, int max_line_length) {
    
    int line_count = 0;

    while(line_count < max_amount_of_lines &&
        fgets(array[line_count], max_line_length, file) != NULL) {

        line_count++;
    }

    fclose(file);

    return line_count;
}

int validate_and_build_menu_array_items(char array[][LINE_MAX_LENGTH], menu_item *menu_array, int array_size) {
    int divider_to_look_for = ';'; // ASCII 59
    char * pointer_to_divider_location = NULL;
    int write_item_index = 0;

    /*
        To get the size of name specified in the struct.
        Cast null pointer 0, to menu_item.
        Access the name field of the stuct.
        Get size of the name with size_t.
    */
    size_t name_size = sizeof(((menu_item *)0)->name);

    for(int line_index = 0; line_index <= array_size; line_index++) {
        pointer_to_divider_location = strchr(array[line_index], divider_to_look_for); // Get pointer to location where ';' exist on the line or NULL 

        if (pointer_to_divider_location != NULL) {
            menu_item item;

            /*
                Calculate the size of menu item name. 
                It is known where the line starts and where the divider is located, 
                so from that it is possible to count the name part length.
            */
            size_t size_of__menu_item_name = pointer_to_divider_location - array[line_index];

            /*
                Check whenever the menu item name is too long.
                Cut the menu item name to fit in the name and make space for null-terminator.
            */
            if (size_of__menu_item_name >= name_size) {
                size_of__menu_item_name = name_size - 1;
            }

            // Copy the characters to the menu item name.
            memcpy(item.name, array[line_index], size_of__menu_item_name);

            // Add null-terminator at the end.
            item.name[size_of__menu_item_name] = '\0';

            // Get menu item price
            validate_and_get_menu_item_price((pointer_to_divider_location+1), &item.price); // hop over the ;

            menu_array[write_item_index] = item;
            write_item_index++;
        }
    }

    

    return write_item_index;
}

void validate_and_get_menu_item_price(char *string, double *price) {
    char *endPointer;
    *price = strtod(string, &endPointer); // Get price (double) from string.

    if (endPointer == string) { // endPointer points to same location as string if no double is found.
        *price = -1.00;
    }
}

void print_out_menu_items(menu_item *array, int array_size) {
    printf("\n%8s\tItem\n", "Price");
    for (int i = 0; i < array_size; i++) {
        if (array[i].price != -1.00 
            && array[i].name[0] != '\0'
            && array[i].name[0] != ' ') {

            printf("%8.2f\t%s\n", array[i].price, array[i].name);
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