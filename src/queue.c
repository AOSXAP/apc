#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

char QUEUE[size][size];
int front = -1, rear = -1;

bool enQueue(char *string){
    if(rear == size - 1)
        return false;
    else{
        //init front
        if(front == -1) front = 0;
        rear++;

        strcpy(*(QUEUE + rear), string);
    }

    return true;
}

bool deQueue(){
    if(front == -1)
        return false;
    else{
        front++;
        if(front > rear){
            front = -1; rear = -1;
        }
    }

    return true;
}

bool print_queue(){
    if(rear == -1)
        return false;
    else{
        printf("\n");
        for(int i = front; i <= rear; i++){
            printf("%i : %s\n", i-front+1, QUEUE[i]);
        }
        printf("\n");
    }

    return true;
}

char* queue_top(){
    if(front != -1)
        return QUEUE[front];
    else return NULL;
}
