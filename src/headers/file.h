#ifndef FILE_H
#define FILE_H

#include <unistd.h>
#include <stdio.h>
#include "file.h"

int file_exists(char *file_name){
    if (access(file_name, F_OK) == 0) {
        return 1;
    }
    return 0;
}

int append_to_file(char *file_name, char *name, char *location){
    FILE *fp = fopen(file_name, "a+");
    if(fp == NULL) return -1;
    fprintf(fp, "%s/%s", name,location);

    fclose(fp);
    return 1;
}

//load into memory when program starts


#endif