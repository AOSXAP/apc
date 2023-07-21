#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <file.h>

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
    int len = 5096;
    char line[len*2];

    fp = fopen(file_name, "r");
    if (fp == NULL) return -1;

    while (fgets(line, len*2, fp) != NULL) {
        char *name, *filepath;

        char* token = strtok(line,";"); //name first
        if(token == NULL) continue;
        name = (char *)malloc(strlen(token) * sizeof(char));
        strcpy(name , token);

        token = strtok(NULL, ";"); //filepath
        if(token == NULL) continue;
        filepath = (char *)malloc(strlen(token) * sizeof(char));
        strcpy(filepath , token);

        if(filepath[strlen(filepath) -1] == '\n')
        filepath[strlen(filepath) - 1] = '\0'; //no \n

        (*f)(name,filepath);
    }

    fclose(fp);

    return 1;
}
