#ifndef LIBRARY_H
#define LIBRARY_H

#define size_lib_path 40096
#define size_lib 5096

struct LIBRARY{
    unsigned int index;
    char    *file_name;
    char    *file_path;
};

extern char LIB_PATH[size_lib_path];

extern struct LIBRARY LIB[size_lib];

extern unsigned int LIB_I;

int compare(char* a, char* b);

//use this with read file
int submit_to_LIB(char* filename , char* path);

void print_LIB();

int load_LIB();

int init_LIB_file();

#endif