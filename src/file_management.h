#ifndef __FILE_MANAGEMENT_H__
#define __FILE_MANAGEMENT_H__

int fm_is_file_executable(const char *file_path);
char* fm_find_path_of_command(const char* command);

#endif /* __FILE_MANAGEMENT_H__ */
