#include "defs.h"

int getImageHandle()
{
	for (int i = 0; i < MAX_NUMBER_IMAGES; i++)
	{
		if (images[i].m_data == NULL) return i;
	}
	return -1;
}

int readBMPFile(char * fileName)
{
	FILE* handle; // Handle to BMP file
	unsigned short int planes; // Must be 1
	unsigned short int bytesPerPixel; // Must be 1

	// Open the file
	errno_t errorCode = fopen_s(&handle, fileName, "rb");
	if (errorCode != 0)
	{
		return -1;
	}

	// Get a valie image handle
	int imageIdx = getImageHandle();
	if (imageIdx == -1) return -1;

	// Go to size data
	fseek(handle, 18, SEEK_CUR);

	if (!(unsigned long)fread(&images[imageIdx].m_width, 4, 1, handle)) {
		return -1;
	}

	// read the height
	if (!(unsigned long)fread(&images[imageIdx].m_height, 4, 1, handle)) {
		return -1;
	}

	// Read the planes
	if (!(fread(&planes, 2, 1, handle))) {
		return -1;
	}
	if (planes != 1) {
		return -1;
	}

	// read the bytes per pixel
	unsigned short int bitsPP;
	if (!((unsigned long)fread(&bitsPP, 2, 1, handle))) {
		return -1;
	}
	bytesPerPixel = bitsPP / 8;

	// Skip past the rest of the bitmap header.
	fseek(handle, 24, SEEK_CUR);

	// Read a 4 BPP bitmap
	if (bytesPerPixel == 4)
	{
		// Not yet defined
		return -1;
	}

	// Read a 3 BPP bitmap
	if (bytesPerPixel == 3)
	{
		// DIB files are 4 byte aligned
		int widthOnDisk = ((images[imageIdx].m_width * 3 + 3) & ~3);
		int sizeOnDisk = widthOnDisk * images[imageIdx].m_height;

		// Actual size without zero padding
		unsigned long size3 = images[imageIdx].m_width * images[imageIdx].m_height * 3;
		unsigned long size4 = images[imageIdx].m_width * images[imageIdx].m_height * 4;


		images[imageIdx].m_data = malloc(sizeof(char)*size4);
		unsigned char *tempImageData = malloc(sizeof(char)*sizeOnDisk);

		if (!(unsigned long)fread(tempImageData, sizeOnDisk, 1, handle)) {
			return -1;
		}

		// DIB files are upside down
		for (int i = images[imageIdx].m_height - 1, l = 0; i >= 0; i--, l++)
		{
			for (unsigned int j = 0, k = 0; j < images[imageIdx].m_width * 4; j += 4, k += 3)
			{
				int memPos = l * widthOnDisk + k;
				unsigned char *memWalker = tempImageData + memPos;
				int imgPos = (i * images[imageIdx].m_width * 4) + j;
				images[imageIdx].m_data[imgPos + 2] = *memWalker;
				images[imageIdx].m_data[imgPos + 1] = *(memWalker + 1);
				images[imageIdx].m_data[imgPos] = *(memWalker + 2);
				images[imageIdx].m_data[imgPos + 3] = 0;;
			}
		}

		free(tempImageData);
		tempImageData = NULL;

		fclose(handle);

		return imageIdx;
	}

	return -1;
}