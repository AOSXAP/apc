#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "../dependencies/miniaudio.h"
#include "queue.h"
#include "file.h"

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
    s_floor = seconds;
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
        convert_seconds(time_l); 
        printf(" - ");
        convert_seconds(s_floor);

        printf("\n");

        return true;
    }
    else if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0){
        UNINIT_MN();
        exit(1);
    }
    else{
        printf("stop / start / queue / play <song> / ... \n");
        return true;
    }

    return false;
}


#endif

//play weird names