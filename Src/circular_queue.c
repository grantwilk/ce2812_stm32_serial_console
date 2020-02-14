/*
file: circular_queue.c
created by: Grant Wilk
date created: 1/26/2020
last modified: 1/26/2020
description: an implementation of a circular queue for characters
*/

# include "circular_queue.h"

/*
Initializes a circular queue and returns it
 @ param void
 @ return the initialized circular queue
*/
circular_queue cq_init( void ) {

    // create a circular queue with default values
    circular_queue cq = {
            .pusher = DEFAULT_PUSHER_POS,
            .puller = DEFAULT_PULLER_POS,
            .isempty = DEFAULT_ISEMPTY,
            .isfull = DEFAULT_ISFULL
    };

    // return the circular queue
    return cq;
}

/*
Pushes an element into the circular queue
@ param cq - the circular queue to push into
@ param c - the character to push into the queue
@ return void
*/
void cq_push( circular_queue * cq, char c ) {

    // push the character into the queue then increment the pusher
    cq->buffer[(cq->pusher)++] = c;

    // if the pusher passes the end of the buffer, put it back at the start of the buffer
    if ( cq->pusher == CIRCULAR_QUEUE_SIZE ) cq->pusher = 0;

    // set the full flag if the pusher moves to the same position as the puller
    cq->isfull = ( cq->pusher == cq->puller );

    // clear the empty flag
    cq->isempty = 0;
}

/*
Pulls the next element from the circular queue
@ param cq - the circular queue to pull from
@ return the character from the queue
*/
char cq_pull( circular_queue * cq ) {

    // pull the character out of the queue and increment the puller
    char c = cq->buffer[(cq->puller)++];

    // if the pusher passes the end of the buffer, put it back at the start of the buffer
    if ( cq->puller == CIRCULAR_QUEUE_SIZE ) cq->puller = 0;

    // set the empty flag if the puller moves to the same position as the pusher
    cq->isempty = ( cq->puller == cq->pusher );

    // clear the full flag
    cq->isfull = 0;

    // return the character
    return c;
}

/*
Clears all values from the circular queue
@ param cq - the circular queue to clear
@ return void
*/
void cq_clear( circular_queue * cq ) {
    cq->pusher = 0;
    cq->puller = 0;
}

/*
Determines whether a circular queue is empty or not
@ param cq - the circular queue to analyze
@ return 1 if the circular queue is empty, 0 otherwise
*/
int cq_isempty( circular_queue * cq ) {
    return cq->isempty;
}

/*
Determines whether a circular queue is full or not
@ param cq - the circular queue to analyze
@ return 1 if the circular queue is full, 0 otherwise
*/
int cq_isfull( circular_queue * cq ) {
    return cq->isfull;
}
