#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "utils.h"

#define MAX_INPUT_COMMAND_LENGTH (100)

int main(int argc, char *argv[]) {

    while(1) {
        
        // Flush after every printf
        setbuf(stdout, NULL); 

        // Uncomment this block to pass the first stage
        printf("$ ");

        // Wait for user input
        char input[MAX_INPUT_COMMAND_LENGTH] = {0};

        // Gets the input arguments from standard input
        fgets(input, GET_ARRAY_SIZE(input), stdin);

        if (input[0] == '\0')
            continue;

        // Add null termination
        input[strlen(input) - 1] = '\0';
        char* args[MAX_INPUT_COMMAND_LENGTH] = {NULL};

        process_command(input, MAX_INPUT_COMMAND_LENGTH, args);

    }
    
    return 0;
}
