#ifndef __COMMANDS_H__
#define __COMMANDS_H__

typedef struct{
    const char *name; // Holds the name of the command
    const int size;
    int (*execute) (const char* input); // Operates on that command
}Command_t;

int action_echo(const char* input);
int action_exit(const char* input);
int action_type(const char* input);

const Command_t* find_command(const char* input);
void process_command(const char* input, int size, char* args[]);
void run_executable(const char* input, int size, char* args[]);

#endif /* __COMMANDS_H__ */

