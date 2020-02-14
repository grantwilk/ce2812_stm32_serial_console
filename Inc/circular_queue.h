/*
file: circular_queue.h
created by: Grant Wilk
date created: 1/26/2020
last modified: 1/26/2020
description: Header file for circular_queue.c
*/

# define CIRCULAR_QUEUE_SIZE 2048
# define DEFAULT_PUSHER_POS 0
# define DEFAULT_PULLER_POS 0
# define DEFAULT_ISEMPTY 1
# define DEFAULT_ISFULL 0

// structure for our circular queue
typedef struct {
    unsigned int pusher;
    unsigned int puller;
    int isempty;
    int isfull;
    char buffer[CIRCULAR_QUEUE_SIZE];
} circular_queue;

// Initializes a circular queue with default values and returns it
circular_queue cq_init( void );

// Pushes an element into the circular queue
void cq_push( circular_queue * cq, char c );

// Pulls the next element from the circular queue
char cq_pull( circular_queue * cq );

// Clears all values from the circular queue
void cq_clear( circular_queue * cq );

// Determines whether a circular queue is empty or not
int cq_isempty( circular_queue * cq );

// Determines whether a circular queue is full or not
int cq_isfull( circular_queue * cq );
