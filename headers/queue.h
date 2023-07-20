#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define size 10000

extern char QUEUE[size][size];

extern int front, rear;

bool enQueue(char *string);

bool deQueue();

bool print_queue();

char* queue_top();
#endif