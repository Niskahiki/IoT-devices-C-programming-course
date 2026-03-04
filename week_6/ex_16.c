/*
Write a program that asks user to enter numbers or to enter end to stop entering numbers. If user
enters any other text except end the program prints an error message and discards the input. The
program must store the numbers in a linked list where each node is dynamically allocated.

typedef struct node {
 int number;
 struct node *next;
} nnode;
 
When user enters end the program prints all entered numbers, frees the allocated memory and then
ends.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define INPUT_MAX_SIZE 10

typedef struct node {
    int number;
    struct node *next;
} nnode;

void read_input(char *str, int max_input_size);
void remove_trailing_whitespace(char *string);
bool convert_string_to_int(char *string, int *number);
void print_numbers_and_free_the_node_from_memory(nnode *numbers);


int main(void) {
    char inputString[INPUT_MAX_SIZE];
    bool continue_asking = true;

    nnode *head = NULL;
    nnode *last = NULL;

    while (continue_asking) {
        printf("\nEnter numbers or enter \"end\" to stop: ");
        read_input(inputString, INPUT_MAX_SIZE);
        remove_trailing_whitespace(inputString);

        if (strcmp(inputString, "end") == 0) {
            if (head == NULL) {
                printf("\nEnd command received. Nothing to show. No numbers entered.\n");
            } else {
                printf("\nEnd command received, here's your numbers:\n");

                print_numbers_and_free_the_node_from_memory(head);

                head = NULL;
                last = NULL;
            }

            continue_asking = false;
        } else {
            int number = 0;
            if (convert_string_to_int(inputString, &number)) {
                nnode *new_node = malloc(sizeof(nnode));

                if (new_node == NULL) {
                    printf("\nFailed to allocate space. Can't store last number.\n");
                } else {

                    new_node->number = number;
                    new_node->next = NULL;

                    if (head == NULL) {
                        head = new_node;
                    } else {
                        last->next = new_node;
                    }

                    last = new_node;
                }
            } else {
                printf("\nInvalid input!\n");
            }
        }
    }

    return 0;
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

bool convert_string_to_int(char *string, int *number) {
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    char *end;
    long value = strtol(string, &end, 10); // 10 means base 10 numbers

    if (*end != '\0') {
        return false;
    }

    *number = (int)value;

    return true;
}

void print_numbers_and_free_the_node_from_memory(nnode *numbers) {
    nnode *current = numbers;
    nnode *next;

    while(current != NULL) {
        next = current->next;
        printf("%d\n", current->number);

        free(current);

        current = next;
    }
}