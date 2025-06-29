#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include "commands.h"
#include "file_management.h"
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

        // Add null termination
        input[strlen(input) - 1] = '\0';

        // Seperate the inputs with ' ' (space) delimitation
        // Initialization of first instance
        char* token_p = strtok(input," ");

        char* args[MAX_INPUT_COMMAND_LENGTH] = {NULL};
        int index = 0;

        // Iterate till Null tokens
        while (token_p != NULL){
            
            // Fetches one token
            printf("%s\n", token_p);

            if (index < MAX_INPUT_COMMAND_LENGTH - 1)
                args[index] = token_p;
            else
                args[index] = NULL;
            
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

        char *path = fm_find_path_of_command(args[0]);

        // Initiate a process and capture id.
        pid_t child = fork();
        int status = 0;

        // Exit with reason when forking fails
        if (child < 0){
            perror("Child forking failed");
            exit(1);
        }

        execv(path, args);

        waitpid(child, &status, 0);

        if (WIFEXITED(status)){
            printf("Exit status of the child was %d\n", (int)WEXITSTATUS(status));
        }

        #if 0
        if (check_command_is_executable(input) == 0){

            // Need to implement shit
        } else {

            process_command(input);
        }
        #endif

    }
    
    return 0;
}
