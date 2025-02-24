#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_COMMAND_LENGTH (100)
#define GET_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Uncomment this block to pass the first stage
  printf("$ ");

  // Wait for user input
  char input[MAX_INPUT_COMMAND_LENGTH] = {0};
  fgets(input, GET_ARRAY_SIZE(input), stdin);

  input[strlen(input) - 1] = '\0';
  printf("%s: command not found\n", input);
  return 0;
}
