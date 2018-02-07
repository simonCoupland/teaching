#pragma once

typedef struct {
	unsigned long width;
	unsigned long height;
	unsigned char *data;
} image;

#define MAX_NUMBER_IMAGES 10
extern image images[MAX_NUMBER_IMAGES];

int readBMPFile(char * fileName);
