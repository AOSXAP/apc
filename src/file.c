#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <stdlib.h>
    #include <limits.h>
#endif

#include <string.h>
#include <stdio.h>

#include "file.h"

int file_exists(char *file_name){
    if (access(file_name, F_OK) == 0) {
        return 1;
    }
    return 0;
}

int append_to_file(const char *file_name, char *name, char *location){
    FILE *file_p = fopen(file_name, "a+");
    if(file_p == NULL) return -1;

    int return_val = fprintf(file_p, "\n%s;%s", name,location);

    int file_closed = fclose(file_p);

    if(return_val > 0 && file_closed == 0) return 1;
    else return 0;
}

int read_file(const char *file_name, int (*function)(char*,char*))
{
    FILE* file_p = NULL;
    char line[LINE_LENGTH];

    file_p = fopen(file_name, "r");

    if (file_p == NULL) return -1;

    while (fgets(line, LINE_LENGTH, file_p) != NULL) {
        char *name = NULL;
        char *filepath = NULL;

        //for strtok_r
        char* saveptr1 = NULL;

        char* token = strtok_r(line,";",&saveptr1); //name first

        if(token == NULL) continue;

        name = (char *)malloc(strlen(token) * sizeof(char));
        strcpy(name, token);

        token = strtok_r(NULL, ";", &saveptr1); //filepath
        if(token == NULL){
            //dealoc name if filepath would be null
            if(name != NULL) free(name);
            continue;
        }

        filepath = (char *)malloc(strlen(token) * sizeof(char));
        strcpy(filepath, token);

        if(filepath[strlen(filepath) -1] == '\n')
            filepath[strlen(filepath) - 1] = '\0'; //no \n

        (*function)(name,filepath);

        if(name != NULL) free(name);
        if(filepath!=NULL) free(filepath);
    }

    int file_closed = fclose(file_p);

    if(file_closed == 0) return 1;
    return 0;
}

char* get_absolute_path(char *file_name){
    #ifdef _WIN32
        char *absolutePath = malloc(MAX_PATH * sizeof(char));
        DWORD pathLength = GetFullPathNameA(file_name, MAX_PATH, absolutePath, NULL);

        if(pathLength != 0)
           return absolutePath
    #else
        char *absolutePath = realpath(file_name, NULL);

        if(absolutePath != NULL) 
            return absolutePath;
    #endif

   return NULL;
}

int delete_file_line(const char *file_name, int line){
    FILE* initial_file = NULL;
    FILE*     tmp_file = NULL;

    //perfect copy - except one line
    initial_file  = fopen(file_name, "r")   ;
    tmp_file      = fopen("delete.tmp", "w");

    int count = 0;
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, initial_file) != NULL){
        if(line != count){
            printf("%s", buffer);
            int return_val = fputs(buffer, tmp_file);

            if(return_val < 0) printf("possible error \n"); 
        }

        count++;
    }

    //close files 
    int initial_file_closed = fclose(initial_file); 
    int tmp_file_closed = fclose(tmp_file);

    
    if(remove(file_name) != 0){
        printf("File cannot be deleted \n");
        return 0;
    }

    if(rename("delete.tmp", file_name) != 0){
        printf("File cannot be renamed \n");
        return 0;
    }

    if(initial_file_closed == 0 && tmp_file_closed == 0)
        return 1;

    return 0;
}

