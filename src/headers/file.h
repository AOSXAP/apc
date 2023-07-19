#ifndef FILE_H
#define FILE_H

int file_exists(char *file_name);

int append_to_file(char *file_name, char *name, char *location);

int read_file(const char *file_name, int (*f)(char*,char*));


#endif