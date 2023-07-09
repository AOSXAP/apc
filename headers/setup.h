#ifndef SETUP_H
#define SETUP_H

ma_result result;
ma_engine engine;
ma_sound sound;

//ma_sound is_playing
bool is_playing = false;
bool is_init = false;

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

    ma_sound_start(&sound);
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

bool mp_command(char *command){
    if(strcmp(command,"stop") == 0)
    {
        return STOP();
    }
    else if(strcmp(command,"play") == 0)
    {
        char argument[10000]; scanf("%s", argument);
        enQueue(argument);

        return true;
    }
    else if(strcmp(command,"queue") == 0){
        return print_queue();
    }
    else if(strcmp(command, "start") == 0){
        return START();
    }
    else if(strcmp(command,"skip") == 0){
        ma_sound_uninit(&sound);
        is_init = false;
        is_playing = false;

        return true;
    }
    else{
        printf("stop / start / queue / play <song> / ... \n");
        return true;
    }

    return false;
}


#endif