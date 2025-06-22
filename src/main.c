#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "file_management.h"

#define MAX_INPUT_COMMAND_LENGTH (100)
#define GET_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

typedef struct{
    const char *name; // Holds the name of the command
    const int size;
    int (*execute) (const char* input); // Operates on that command
}Command_t;

const Command_t* find_command(const char* input);

int action_echo(const char* input)
{   
    printf("%s\n", input);
    return 0;
}

int action_exit(const char* input)
{   
    if (strncmp(input, "0", strlen("0")) == 0)
        exit(0);
    else
        exit(1);
}

int action_type(const char* input)
{
    //printf("1:%s\n", input);
    const Command_t *command = find_command(input);

    if (command)
    {
        //printf("2:%s\n", command->name);
        printf("%s is a shell builtin\n", input);
    }
    else
    {
        char *path = utils_fm_find_path_of_command(input);
        
        if (path != NULL)
        {
            printf("%s is %s\n", input, path);
        }
        else
        {
          printf("%s: not found\n", input);
        }
    }
    return 0;
}

static const Command_t commands[] = {
    {"echo", 4, &action_echo},
    {"exit", 4, &action_exit},
    {"type", 4, &action_type},
};

#define MAX_COMMAND_LIST (GET_ARRAY_SIZE(commands))

const Command_t* find_command(const char* input)
{
    for (int index = 0; index < MAX_COMMAND_LIST; index++)
    {
        if (strncmp(input, commands[index].name, commands[index].size) == 0)
        {
            return (&commands[index]);
        }
    }

    return NULL;
}

void process_command(const char* input)
{
    const Command_t *command = find_command(input);

    if (command){
        command->execute((input + command->size + 1));
    } else {
        printf("Unknown command: %s\n", input);
    }
}


int main(int argc, char *argv[]) {

    while(1)
    {
        // Flush after every printf
        setbuf(stdout, NULL); 

        // Uncomment this block to pass the first stage
        printf("$ ");

        // Wait for user input
        char input[MAX_INPUT_COMMAND_LENGTH] = {0};

        fgets(input, GET_ARRAY_SIZE(input), stdin);

        input[strlen(input) - 1] = '\0'; // Add null termination

        process_command(input);

    }
    return 0;
}
