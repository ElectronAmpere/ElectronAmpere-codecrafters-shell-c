#include <stdio.h>
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
int utils_fm_is_file_executable(const char *file_path);
{
    int result = false;

    result = (access(path, X_OK) == 0);

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
    char* dir = strtok(env_p, ":");

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
