#pragma once

// Data needed for each image
typedef struct {
	unsigned long m_width;
	unsigned long m_height;
	unsigned char *m_data;
} image;

// Storage for images
#define MAX_NUMBER_IMAGES 10
extern image images[MAX_NUMBER_IMAGES];

// Read a windows BMp or Device Independant Bitmap to memory
int readBMPFile(char * fileName);
