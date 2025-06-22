#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "file_management.h"

#define ENV_PATH_NAME "PATH"
#define FILE_PATH_LENGTH_MAX (1024)
static char full_path_g[FILE_PATH_LENGTH_MAX];

/**
 * @brief      { function_description }
 *
 * @param[in]  file_path  The file path
 *
 * @return     { description_of_the_return_value }
 */
int utils_fm_is_file_executable(const char *file_path)
{
    int result = false;

    result = (access(file_path, X_OK) == 0);

    return (result);
}

/**
 * @brief      { function_description }
 *
 * @param[in]  command  The command
 *
 * @return     { description_of_the_return_value }
 */
char *utils_fm_find_path_of_command(const char* command)
{
    char *env_p = getenv(ENV_PATH_NAME);

    if(env_p == NULL)
        return NULL;

    char* path_cpy = strdup(env_p);
    /**
     * Bug Details:
     *  Line: char* dir = strtok(env_p, ":");
     *  Problem: strtok modifies its input string (env_p) by inserting null terminators. 
     *      Since env_p is from getenv, this may corrupt the environment or cause undefined behavior.
     *  Consequence: The first call to utils_fm_find_path_of_command (e.g., for cp) may work if 
     *      cp is found before PATH is fully corrupted. Subsequent calls (e.g., for ls) fail because 
     *      env_p is already modified, and strtok cannot continue tokenizing correctly.
     *  Fix: Use path_cpy (the duplicated string) for tokenization, as it’s safe to modify.
     */ 
    char* dir = strtok(path_cpy, ":");

    while(dir != NULL)
    {
        snprintf(full_path_g, sizeof(full_path_g), "%s/%s", dir, command);

        /* Check if the path is an executable or not */
        if(utils_fm_is_file_executable(full_path_g)){
            free(path_cpy);

            return full_path_g;
        }

        dir = strtok(NULL, ":");
    }

    free(path_cpy);
    return NULL;
}
