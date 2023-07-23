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

#define MS_TO_NS(ms) ((ms) * 1000000ULL)

mtx_t mut; // NOLINT

int manager(void * data) {
    const atomic_bool * const stop_token = (atomic_bool*)(data);

    while(*stop_token == false) {
        int status = mtx_lock(&mut);

        if(!MN_PLAYS() || is_init == false) {
            time_l = time(NULL);

            if(queue_top() != NULL) {
                //is_playing = true;
                if(is_init == true) ma_sound_uninit(&sound);
                PLAY(queue_top());
            } else is_playing = false;
        }

        status = mtx_unlock(&mut);

        status =
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

    int status = mtx_init(&mut, mtx_plain);

    if(status == thrd_error) return 0;

    status = thrd_create(&audio_manager, manager, &stop_token);

    if(status == thrd_error || status == thrd_nomem)
        return 0;

    status = thrd_detach(audio_manager);

    if(status == thrd_error) return status;

    while(true) {
        char command[CMD_SIZE];

        printf("APC_ ");
        status = scanf("%s", command);

        if(status == EOF) return status;

        if(strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
            break;

        status = mtx_lock(&mut);

        mp_command(command);

        status = mtx_unlock(&mut);
    }

    UNINIT_MN();

    stop_token = true;

    int manager_state = 0;

    status = thrd_join(audio_manager, &manager_state);

    if(status == thrd_error) return status;

    mtx_destroy(&mut);

    return manager_state;
}
