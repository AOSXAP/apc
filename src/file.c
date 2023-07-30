#ifdef _WIN32
    #include <stdio.h>
    #include <windows.h>
#else
    #define _GNU_SOURCE

    #include <unistd.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <limits.h>
#endif

#include <file.h>

#define BUFFER_SIZE 1000

int file_exists(char *file_name){
    if (access(file_name, F_OK) == 0) {
        return 1;
    }
    return 0;
}

int append_to_file(const char *file_name, char *name, char *location){
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

char* get_relative_path(char *file_name){
   #ifdef _WIN32
        char absolutePath[MAX_PATH];
        DWORD pathLength = GetFullPathNameA(file_name, MAX_PATH, absolutePath, NULL);

        if(pathLength == 0){
            printf("file not found");
        }else{
            printf("%s",absolutePath);
        }
   #else
        char *absolutePath = realpath(file_name, NULL);

        if(absolutePath == NULL){
            printf("file not found");
        }else printf("%s",absolutePath);

        free(absolutePath);
   #endif

   return "";
}

int delete_file_line(const char *file_name, int line){
    FILE *initial_file, *tmp_file;

    //perfect copy - except one line
    initial_file  = fopen(file_name, "r");
    tmp_file = fopen("delete.tmp", "w");

    int count = 0;
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, initial_file) != NULL){
        if(line != count){
            printf("%s", buffer);
            fputs(buffer, tmp_file);
        }

        count++;
    }

    //close files 
    fclose(initial_file); fclose(tmp_file);

    
    if(remove(file_name) != 0){
        printf("File cannot be deleted \n");
        return 0;
    }

    if(rename("delete.tmp", file_name) != 0){
        printf("File cannot be renamed \n");
        return 0;
    }

    return 1;
}

