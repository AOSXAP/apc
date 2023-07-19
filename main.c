#define MINIAUDIO_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "src/dependencies/miniaudio.h"
#include "src/headers/queue.h"
#include "src/headers/setup.h"

void* task() {
    while(true){
        if(!MN_PLAYS() || is_init == false){
            time_l = 0;
            if(queue_top() != NULL){
                //is_playing = true;
                if(is_init == true) ma_sound_uninit(&sound);
                PLAY(queue_top());
            }else is_playing = false;
        }
        if(is_playing) time_l++;
        sleep(1);
    }

    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    //load songs
    //binary search in C 

    INIT_MN();
    int p_id = getpid();
    printf("Process ID: %d\n", p_id);

    pthread_t thread;
    int ret = pthread_create(&thread, NULL, task, NULL);

    while(true){
        char command[1000], argument[1000];
        printf("APC_ ");
        scanf("%s", command);

        mp_command(command);
    }

    UNINIT_MN();
    return 0;
}