#ifndef FILE_H
#define FILE_H

enum {
    BUFFER_SIZE  = 1000,
    LINE_LENGTH = 10000
};

int file_exists(char *file_name);

int append_to_file(const char *file_name, char *name, char *location);

int read_file(const char *file_name, int (*f)(char*,char*));

int delete_file_line(const char *file_name, int line);

char* get_absolute_path(char *file_name);

#endif