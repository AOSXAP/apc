#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
    fprintf(fp, "\n%s;%s", name,location);

    fclose(fp);
    return 1;
}

int read_file(const char *file_name, int (*f)(char*,char*))
{
    FILE* fp;
    char* line = NULL;
    unsigned long len = 0;
    long read;

    fp = fopen(file_name, "r");
    if (fp == NULL) return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        char name[5096], filepath[5096 * 2];
        
        char* token = strtok(line,";"); //name first
        strcpy(name , token); 
        
        token = strtok(NULL, ";"); //filepath
        strcpy(filepath , token);
        filepath[strlen(filepath) - 1] = '\0'; //no \n
        
        (*f)(name,filepath);
    }

    fclose(fp);
    if (line) free(line);

    return 1;
}