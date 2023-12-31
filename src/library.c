#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "library.h"
#include "file.h"

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

char LIB_PATH[size_lib_path] = "src/saved.txt";

struct LIBRARY LIB[size_lib];
unsigned int LIB_I = 0;

int compare(char* a, char* b){
    int comp = strcmp(a , b);

    if(comp == 0)     return  0;
    else if(comp > 0) return  1;
    else              return -1;

}

//use this with read file
int submit_to_LIB(char* filename , char* path){
    LIB[LIB_I].index = LIB_I;
    
    LIB[LIB_I].file_name = (char *)malloc(strlen(filename) * sizeof(char));
    LIB[LIB_I].file_path = (char *)malloc(strlen(path)     * sizeof(char));

    strcpy(LIB[LIB_I].file_name, filename);
    strcpy(LIB[LIB_I].file_path, path);

    LIB_I += 1;
    return   1;
}

void print_LIB(){
    for(unsigned int index = 0; index < LIB_I; index++){
        printf("%d\t%s\t%s \n"   ,
            LIB[index].index     ,
            LIB[index].file_name ,
            LIB[index].file_path
        );
    }

    printf("\n");
}

int init_LIB_file(){
    if (access(LIB_PATH, F_OK) != 0) {
        FILE *fp = NULL;
        fp = fopen (LIB_PATH, "a");
        
        if(fp != NULL) fclose(fp);
    } 

    return 1;
}

int load_LIB(void){
    //read from saved.txt and load results in LIB

    //get path of binary
    char buffer[size_lib_path];
    readlink("/proc/self/exe", buffer, size_lib_path);

    //eliminate bin/apc from path
    strcpy(LIB_PATH,buffer);
    LIB_PATH[strlen(LIB_PATH) - 7] = '\0';

    //add element to path
    strcat(LIB_PATH, "src/saved.txt");

    printf("LIB_FILE_PATH: %s\n", LIB_PATH);
    init_LIB_file();

    read_file(LIB_PATH , &submit_to_LIB);
    return 1;
}
