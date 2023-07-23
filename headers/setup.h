#ifndef SETUP_H
#define SETUP_H

#include <stdbool.h>

#include <miniaudio.h>

extern ma_result result;
extern ma_engine engine;
extern ma_sound sound;

//ma_sound is_playing
extern bool is_playing;
extern bool is_init   ;

extern time_t time_l ; //current time of sound
extern int s_floor; //total time of sound

bool INIT_MN();

bool UNINIT_MN();

bool PLAY(char *arg);

bool STOP();

bool START();

bool MN_PLAYS();

void convert_seconds(time_t sec);

bool mp_command(char *command);

#endif
