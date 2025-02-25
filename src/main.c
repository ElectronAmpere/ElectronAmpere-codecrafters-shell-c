#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_COMMAND_LENGTH (100)
#define GET_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

int main(int argc, char *argv[]) {

  while(1)
  {
    // Flush after every printf
    setbuf(stdout, NULL); 

    // Uncomment this block to pass the first stage
    printf("$ ");

    // Wait for user input
    char input[MAX_INPUT_COMMAND_LENGTH] = {0};
    char exit_cmd[] = "exit 0";
    char echo_cmd[] = "echo";
    char type_cmd[] = "type"

    fgets(input, GET_ARRAY_SIZE(input), stdin);

    input[strlen(input) - 1] = '\0';
    if (strncmp(input, exit_cmd, strlen(exit_cmd)) == 0)
    {
      return 0;
    }
    else if (strncmp(input, echo_cmd, strlen(echo_cmd)) == 0)
    {
      printf("%s\n", input + strlen(echo_cmd) + 1);
      continue;
    }
    else if (strncmp(input, type_cmd, strlen(type_cmd)) == 0)
    {
      if (strncmp((input + strlen(type_cmd) + 1), type_cmd, strlen(type_cmd)) == 0)
      {
        printf("%s is a shell builtin\n", input + strlen(type_cmd) + 1);
      }
      else if (strncmp((input + strlen(exit_cmd) + 1), exit_cmd, strlen(exit_cmd)) == 0)
      {
        printf("%s is a shell builtin\n", input + strlen(exit_cmd) + 1);
      }
      else if (strncmp((input + strlen(echo_cmd) + 1), echo_cmd, strlen(echo_cmd)) == 0)
      {
        printf("%s is a shell builtin\n", input + strlen(echo_cmd) + 1);
      }
      else
      {
        printf("%s: command not found\n", input);
      }
    }
    else
    {
      printf("%s: command not found\n", input);
    }
  }
  return 0;
}
