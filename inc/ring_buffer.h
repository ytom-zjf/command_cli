#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <string.h>

#define RING_BUFFER_MAX_SIZE	128

typedef struct ring_buffer
{
	volatile unsigned int pR;
	volatile unsigned int pW;
	unsigned char buffer[RING_BUFFER_MAX_SIZE];
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *buf);
void ring_buffer_write(char c, ring_buffer_t *buf);
int ring_buffer_read(char *c, ring_buffer_t *buf);

#endif