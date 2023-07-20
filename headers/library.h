#ifndef LIBRARY_H
#define LIBRARY_H

#define size_lib 5096

struct LIBRARY{
    int index;
    char file_name[size_lib];
    char file_path[size_lib * 2];
};

extern struct LIBRARY LIB[size_lib];

extern unsigned int LIB_I;

int compare(char* a, char* b);

//use this with read file
int submit_to_LIB(char* filename , char* path);

void print_LIB();

int load_LIB();

#endif