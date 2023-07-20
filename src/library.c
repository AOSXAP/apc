#include <string.h>
#include <stdio.h>

#include <library.h>
#include <file.h>

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
    for(int index = 0; index < LIB_I; index++){
        printf("%d\t%s\t%s \n"   ,
            LIB[index].index     ,
            LIB[index].file_name ,
            LIB[index].file_path
        );
    }

    printf("\n");
}


int load_LIB(){
    //read from saved.txt and load results in LIB
    read_file("src/saved.txt" , &submit_to_LIB);
    return 1;
}
