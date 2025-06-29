#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "commands.h"
#include "utils.h"
#include "file_management.h"

static const Command_t commands[] = {
    {"echo", 4, &action_echo},
    {"exit", 4, &action_exit},
    {"type", 4, &action_type},
};

#define MAX_COMMAND_LIST (GET_ARRAY_SIZE(commands))

int action_echo(const char* input) {   
    
    printf("%s\n", input);
    
    return 0;
}

int action_exit(const char* input) {   
    
    if (strncmp(input, "0", strlen("0")) == 0)
        exit(0);
    else
        exit(1);
}

int action_type(const char* input) {
    
    const Command_t *command = find_command(input);

    if (command) {
        printf("%s is a shell builtin\n", input);
    } else {
        char *path = fm_find_path_of_command(input);
        
        if (path != NULL)
            printf("%s is %s\n", input, path);
        else
            printf("%s: not found\n", input);
    }

    return 0;
}

const Command_t* find_command(const char* input) {
    
    for (int index = 0; index < MAX_COMMAND_LIST; index++) {
        if (strncmp(input, commands[index].name, commands[index].size) == 0)
            return (&commands[index]);
    }

    return NULL;
}

void run_executable(const char* input, int size, char* args[]){

        // Seperate the inputs with ' ' (space) delimitation
    // Initialization of first instance
    char* token_p = strtok((char* )input," ");
    int index = 0;

    // Iterate till Null tokens
    while (token_p != NULL) {
        
        // Fetches one token
        if (index >= size - 1)
            break;

        args[index] = token_p;
        
        /* 
            * String Token = strtok
            * If the input is Null then the previous input is tokenized. 
            * 
            * Note: 
            * The tokenization is only applicable when the pervious call
            * to the strtok has input other than null. The tokens are exhausted
            * once all the tokens created from the first instance is retrieved.
            * 
            * If incase that the following calls are given input say other than
            * NULL the token will be repeated indefinitely.
            * Eg: token_p = strtok(input, " "); within any loop (not recommended).
            */

        token_p = strtok(NULL, " ");
        index++;
    }

    args[index] = NULL;
    char *path = NULL;

    // how to validate args?
    if (args[0] != NULL)
        path = fm_find_path_of_command(args[0]);

    // Initiate a process and capture id.
    pid_t child = fork();
    int status = 0;

    // Exit with reason when forking fails
    if (child == 0) {

        if (path != NULL)
            execv(path, args);
        else
            printf("%s: command not found\n", args[0]);

    } else if (child > 0) {

        waitpid(child, &status, 0);

        if (WIFEXITED(status)) {

            // commented since the output is taken as test failure
            //printf("Exit status of the child was %d\n", (int)WEXITSTATUS(status));
        }

    } else {

        perror("Child forking failed");
    }
}

void process_command(const char* input, int size, char* args[]) {

    const Command_t *command = find_command(input);

    if (command)
        command->execute((input + command->size + 1));
    else
        //printf("%s: not found\n", input);
        run_executable(input, size, args);
}
