#include "ringbuffer.h"
#include <stddef.h>
#include <stdlib.h>

//#define DEBUG_MESSAGES_ON
#ifdef DEBUG_MESSAGES_ON
#include <stdio.h>
#endif


RingBuffer* ring_create(int maxSize) {
  //The two nullpointer return checks do not come from TDD. No idea how to force an exception in malloc.
  RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
  if(!buffer)
    return (RingBuffer*) NULL;

  int *buffer_data = (int *)malloc(sizeof(int) * maxSize);
  if(!buffer_data)
  {
    free(buffer);
    return (RingBuffer*) NULL;
  }
  buffer->data = buffer_data;
  buffer->nbOfElements = buffer->offRead = buffer->offWrite = 0;
  buffer->maxNbOfElements = maxSize;
  return buffer;
}

void ring_delete(RingBuffer *buffer) {
  if(buffer->data)
  {
    free(buffer->data);
    buffer->data = NULL;
  }
    
  if(buffer)
  {
    free(buffer); 
    buffer = NULL;
  }
}

void ring_add(RingBuffer *buffer, int element) {
  buffer->nbOfElements += 1;
  if(buffer->nbOfElements > buffer->maxNbOfElements){ //check if full
    buffer->nbOfElements -= 1;
    return;
  }
  #ifdef DEBUG_MESSAGES_ON
  printf("Added element %d, Value %d\n", element, buffer->nbOfElements);
  #endif

//add element and set new offset
  buffer->data[buffer->offWrite] = element;
  buffer->offWrite = (buffer->offWrite + 1) % buffer->maxNbOfElements;
}

bool ring_remove(RingBuffer *buffer, int *result) { 
  if(0 == buffer->nbOfElements){
    return false;
  }

  buffer->nbOfElements -= 1;
  *result = buffer->data[buffer->offRead];
  buffer->offRead = (buffer->offRead + 1) % buffer->maxNbOfElements;

  #ifdef DEBUG_MESSAGES_ON
  printf("Popped element %d, Value %d\n", *result, buffer->nbOfElements);
  #endif
  return true; 
}
