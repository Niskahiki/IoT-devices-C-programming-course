/*
    Extend program of Ex15 so that after reading the file content the program asks user to choose
    sorting order of the menu. User can choose to sort by price or by name.

    Write comparison functions for sorting by name and by price and use qsort() from standard library
    to sort the array before printing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ARRAY_SIZE 40
#define STRING_SIZE 256
#define LINE_MAX_LENGTH 60

typedef struct menu_item_ {
    char name[50];
    double price;
} menu_item;

typedef enum {
    Price,
    Name
} sort_order_type ;

void ask_user_for_file_name(char *fileName, int fileName_max_size);
sort_order_type ask_user_for_sort_order(int string_max_size);

int read_file_lines_to_array(char array[][LINE_MAX_LENGTH], FILE *file, int max_amount_of_lines, int max_line_length);
int validate_and_build_menu_array_items(char array[][LINE_MAX_LENGTH], menu_item *menu_array, int array_size);
void validate_and_get_menu_item_price(char *string, double *price);

int compare_menu_item_price(const void *item1, const void *itme2);
int compare_menu_item_name(const void *item1, const void *item2);

void print_out_menu_items(menu_item *array, int array_size);
void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);


int main(void) {
    
    char fileName[STRING_SIZE];

    ask_user_for_file_name(fileName, STRING_SIZE);

    FILE *file;

    file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s\n", fileName);
        exit(1);
    }

    char lines[ARRAY_SIZE][LINE_MAX_LENGTH];
    int array_size = read_file_lines_to_array(lines, file, ARRAY_SIZE, LINE_MAX_LENGTH);

    menu_item menu_array[array_size];
    int menu_array_size = validate_and_build_menu_array_items(lines, menu_array, array_size);

    if (menu_array_size == 0) {
        printf("The file has no valid menu lines. Quiting...\n");
        return 0;
    }

    sort_order_type sort_type = ask_user_for_sort_order(STRING_SIZE);

    if (sort_type == Price) {
        qsort(menu_array, menu_array_size, sizeof(menu_item), compare_menu_item_price);
    } else {
        qsort(menu_array, menu_array_size, sizeof(menu_item), compare_menu_item_name);
    }

    print_out_menu_items(menu_array, menu_array_size);

    return 0;
}

void ask_user_for_file_name(char *fileName, int fileName_max_size) {
    printf("Enter filename to open: ");
    read_input(fileName, fileName_max_size);
    remove_trailing_whitespace(fileName);
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

sort_order_type ask_user_for_sort_order(int string_max_size) {
    bool has_valid_sort_type = false;
    char sort_type_str[string_max_size];

    while (!has_valid_sort_type) {
        printf("Enter sort order. Enter \"price\" or \"name\": ");
        read_input(sort_type_str, string_max_size);
        remove_trailing_whitespace(sort_type_str);

        if (strcmp(sort_type_str, "price") == 0) {
            return Price;
        } else if (strcmp(sort_type_str, "name") == 0) {
            return Name;
        } else {
            printf("Invalid input!\n");
        }
    }
}

int compare_menu_item_price(const void *item1, const void *item2) {
    return(((menu_item *)item1)->price - ((menu_item *)item2)->price);
}

/*
    I took inspiration for this function from: https://stackoverflow.com/questions/31127260/strcasecmp-a-non-standard-function.
    From author chux (https://stackoverflow.com/users/2410359/chux).

    Could not have written this function all by my self.
    The strcmp() sees all upper case letters higher than lower case letters, because of ASCII values.
    Which causes strcmp() to see that 'Z' > 'a'.

    The function is not copy of chux's function.
    I edited it for my own use case, for exmaple by replacing 'tolower(toupper())' with just 'tolower()', because I don't have to worry about negative values.
*/
int string_non_case_sensitive_compare(const char *a, const char *b) {
    int ca, cb;

    do {
        /*
            Get characters from the string at the same index.
            Later the a and b are +=1, which makes the a and b to point to the next character of the string,
            and this goes on as long as the characters are equal or end of string is countered.
        */
        ca = *(unsigned char *) a;
        cb = *(unsigned char *) b;

        // Both of the characters to lower case.
        ca = tolower(ca);
        cb = tolower(cb);

        // Hop to point to the next character of the string.
        a++;
        b++;
    } while (ca == cb && ca != '\0'); // Continue as long as the characters are the same and not end of string.

    // The characters don't match or end of string is countered.
    return ca - cb;
}

int compare_menu_item_name(const void *item1, const void *item2) {
    return string_non_case_sensitive_compare(((menu_item *)item1)->name, ((menu_item *)item2)->name);
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
