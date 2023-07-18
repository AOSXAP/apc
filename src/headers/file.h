#ifndef FILE_H
#define FILE_H

#include <unistd.h>
#include "file.h"

int file_exists(char *file_name){
    if (access(file_name, F_OK) == 0) {
        return 1;
    }
    return 0;
}


#endif