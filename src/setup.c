
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <miniaudio.h>
#include "queue.h"
#include "file.h"
#include "library.h"
#include "setup.h"

ma_result result;
ma_engine engine;
ma_sound sound;

//ma_sound is_playing
bool is_playing = false;
bool is_init    = false;

int time_l  = 0; //current time of sound
int s_floor = 0; //total time of sound

bool INIT_MN(){
    result = ma_engine_init(NULL, &engine);

    if (result != MA_SUCCESS) {
        return false;
    }

    return true;
}

bool UNINIT_MN(){
    ma_engine_uninit(&engine); return true;
}

bool PLAY(char *arg){
    //ma_engine_play_sound(&engine, arg, NULL);
    //if(is_playing) ma_sound_uninit(&sound);
    ma_sound_init_from_file(&engine, arg, 0, NULL, NULL, &sound);
    is_init = true;

    float seconds;
    ma_sound_get_length_in_seconds(&sound, &seconds);
    s_floor = (int)seconds;
    time_l = 0;

    ma_sound_start(&sound);
    is_playing = true;
    deQueue();

    return true;
}

bool STOP(){
    ma_engine_stop(&engine); return true;
}

bool START(){
    ma_engine_start(&engine); return true;
}

bool MN_PLAYS(){
    if(ma_sound_is_playing(&sound)) return true;
    return false;
}

void convert_seconds(int sec){
    int h = sec /3600;
    int m = (sec -(3600*h))/60;
	int s = sec -(3600*h)-(m*60);

    printf("%d:%d:%d",h,m,s);
}

bool mp_command(char *command){
    if(strcmp(command,"stop") == 0)
    {
        is_playing = false;
        return STOP();
    }
    else if(strcmp(command,"play") == 0)
    {
        char argument[10000];
        scanf(" %[^\n]",argument);
        //printf("%s", argument);

        if(file_exists(argument))
            enQueue(argument);
        else{
            printf("\nfile does not exist! \n\n");
        }


        return true;
    }
    else if(strcmp(command,"queue") == 0){
        return print_queue();
    }
    else if(strcmp(command, "resume") == 0){
        is_playing = true;
        return START();
    }
    else if(strcmp(command,"skip") == 0){
        if(is_playing){
            ma_sound_uninit(&sound);
            is_init = false;
            is_playing = false;
        }
        return true;
    }
    else if(strcmp(command, "clear") == 0){
        system("clear");
    }
    else if(strcmp(command, "time") == 0){
        //more efficient implementation needed
        if(!is_playing){
            printf("song not playing");
        }else{
            convert_seconds(time_l);
            printf(" - ");
            convert_seconds(s_floor);
        }
        printf("\n");

        return true;
    }
    else if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
        UNINIT_MN();
        exit(1);
    }
    else if(strcmp(command, "lib") == 0){
        print_LIB();
    }
    else if(strcmp(command, "la") == 0 || strcmp(command, "lib-add") == 0){
        printf("path: ");
        char path[10000]; scanf(" %[^\n]",path);

        printf("name: ");
        char name[1000]; scanf(" %[^\n]",name);

        //handle if file has \n before and after, fix errors
        //also it would be better sto store full path
        

        if(file_exists(path)){
            char *pathx = get_absolute_path(path);
            submit_to_LIB(name,pathx);
            append_to_file(LIB_PATH , name, pathx);

            printf("file submitted and stored\n\n");
            free(pathx);

            return true;
        }else{
            printf("file does not exist\n\n");
        }

        return false;
    }
    else if(strcmp(command , "pl") == 0 || strcmp(command , "lib-play") == 0){
        int selected_index = -1;
        scanf("%d", &selected_index);

        if(file_exists(LIB[selected_index].file_path)){
            enQueue(LIB[selected_index].file_path);

            printf("%s %s\n\n", LIB[selected_index].file_path, LIB[selected_index].file_name);
        }
        else{
            printf("\nfile does not exist! \n\n");
        }

        return true;
    }
    else{
        printf("stop / resume / queue / play <song> / time ... \n");
        return true;
    }

    return false;
}
