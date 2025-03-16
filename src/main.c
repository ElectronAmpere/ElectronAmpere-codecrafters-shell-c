#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_COMMAND_LENGTH (100)
#define MAX_PATH_ARRAY_LENGTH (1024)
#define GET_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

#define ENV_PATH_NAME "PATH"
static char full_path[MAX_PATH_ARRAY_LENGTH];

int is_executable(const char *path)
{
  return (access(path, X_OK) == 0);
}

char *find_path(const char* command)
{
  char *env_p = getenv(ENV_PATH_NAME);
  if (env_p == NULL)
    return NULL;

  char* path_cpy = strdup(env_p);
  char* dir = strtok(env_p, ":");

  while (dir != NULL){
    snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
    if (is_executable(full_path)){
      free(path_cpy);
      return full_path;
    } 
    dir = strtok(NULL, ":");
  }

  free(path_cpy);
  return NULL;
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
    char exit_cmd[] = "exit";
    char echo_cmd[] = "echo";
    char type_cmd[] = "type";

    fgets(input, GET_ARRAY_SIZE(input), stdin);

    input[strlen(input) - 1] = '\0';
    if ((strncmp(input, exit_cmd, strlen(exit_cmd)) == 0)
      &&(strncmp((input + strlen(exit_cmd)), " 0", strlen(" 0")) == 0))
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
        char *path = find_path((input + strlen(type_cmd) + 1));
        if (path != NULL)
        {
          printf("%s is %s\n", (input + strlen(type_cmd) + 1), path);
        }
        else
        {
          printf("%s: not found\n", (input + strlen(type_cmd) + 1));
        }
      }
    }
    else
    {
      printf("%s: command not found\n", input);
    }
  }
  return 0;
}
