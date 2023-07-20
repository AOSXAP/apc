#define MINIAUDIO_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <stdatomic.h>

#include <miniaudio.h>
#include <queue.h>
#include <setup.h>
#include <library.h>

#define MS_TO_NS(ms) (ms * 1000000ULL)

int manager(void * data) {
    const atomic_bool * const stop_token = (atomic_bool*)(data);

    while(*stop_token == false) {
        if(!MN_PLAYS() || is_init == false) {
            time_l = 0;

            if(queue_top() != NULL) {
                //is_playing = true;
                if(is_init == true) ma_sound_uninit(&sound);
                PLAY(queue_top());
            } else is_playing = false;
        }

        if(is_playing) time_l++;

        const int status =
            thrd_sleep(&(struct timespec){ .tv_nsec = MS_TO_NS(1ULL) }, NULL);

        if(status != 0) return status;
    }

    return 0;
}

#define CMD_SIZE 1000

int main(void) {

    if(load_LIB()){
        //loaded lib of songs
        printf("__Library Loaded__\n");
    }

    INIT_MN();

    thrd_t audio_manager = 0;

    atomic_bool stop_token = false;

    int status = thrd_create(&audio_manager, manager, &stop_token);

    if(status == thrd_error || status == thrd_nomem)
        return 0;

    status = thrd_detach(audio_manager);

    if(status == thrd_error) return status;

    while(true) {
        char command[CMD_SIZE];

        printf("APC_ ");
        status = scanf("%s", command);

        if(status == EOF) return status;

        mp_command(command);
    }

    UNINIT_MN();

    stop_token = true;

    int manager_state = 0;

    status = thrd_join(audio_manager, &manager_state);

    if(status == thrd_error) return status;

    return manager_state;
}
