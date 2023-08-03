#define MINIAUDIO_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

#include <miniaudio.h>
#include "queue.h"
#include "setup.h"
#include "library.h"
#include "file.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER ;


void* task() {
    while(true){
        pthread_mutex_lock(&lock);

        if(!MN_PLAYS() || is_init == false){
            time_l = 0;
            if(queue_top() != NULL){
                //is_playing = true;
                if(is_init == true) ma_sound_uninit(&sound);
                PLAY(queue_top());
            }else is_playing = false;
        }
        if(is_playing) time_l++;

        struct timespec tm_val;

        clock_gettime(CLOCK_REALTIME, &tm_val);
	    tm_val.tv_sec += 1;

        pthread_cond_timedwait(&cond, &lock, &tm_val);

        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}


int main()
{
    if(load_LIB()){
        //loaded lib of songs
        printf("__Library Loaded__\n\n");
    }

    INIT_MN();
    int p_id = getpid();
    printf("Process ID: %d\n\n", p_id);

    pthread_t thread = 0;
    pthread_create(&thread, NULL, task, NULL);

    while(true){
        char command[BUFFER_SIZE] = "\0";
        printf("APC_ ");
        int scan_return = scanf("%s", command);
        
        if(scan_return > 0)
            mp_command(command);
    }

    UNINIT_MN();
    return 0;
}
