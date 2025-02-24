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
    char exit_string[] = "exit 0";
    char echo_string[] = "echo";
    fgets(input, GET_ARRAY_SIZE(input), stdin);

    input[strlen(input) - 1] = '\0';
    if (strncmp(input, exit_string, strlen(exit_string)) == 0)
    {
      return 0;
    }
    else if (strncmp(input, echo_string, strlen(echo_string)) == 0)
    {
      printf("%s\n", input + strlen(echo_string) + 1);
      continue;
    }
    else
    {
      printf("%s: command not found\n", input);
    }
  }
  return 0;
}
