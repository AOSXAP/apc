#define MINIAUDIO_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "dependencies/miniaudio.h"
#include "headers/queue.h"
#include "headers/setup.h"


void* task() {
    while(true){
        if(!MN_PLAYS() || is_init == false){
            if(queue_top() != NULL){
                //is_playing = true;
                if(is_init == true) ma_sound_uninit(&sound);
                PLAY(queue_top());
            }else is_playing = false;
        }
        sleep(1);
    }

    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    INIT_MN();
    int p_id = getpid();
    printf("Process ID: %d\n", p_id);

    pthread_t thread;
    int ret = pthread_create(&thread, NULL, task, NULL);

    while(true){
        char command[1000], argument[1000];
        printf("music_player >>> ");
        scanf("%s", command);

        mp_command(command);
    }

    UNINIT_MN();
    return 0;
}