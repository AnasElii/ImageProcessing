#pragma warning(disable:4996)
#include <iostream>

#define BMP_HEADER_SIZE			 54
#define BMP_COLOR_TABLE_SIZE	1024
#define CUSTOM_IMG_SIZE         1000*1000

// Read from image
void imgReader(const char* imgPath, int* _width, int* _height, int* _depth, unsigned char* _header, unsigned char* _colorTable, unsigned char* _buffer )
{
	FILE* fIn = fopen(imgPath, "rb");

	if (fIn == (FILE*)0)
		std::cout << "Unable to open image" << std::endl;

	for (unsigned int i = 0; i < BMP_HEADER_SIZE; i++)
		_header[i] = getc(fIn);

	*_width = *(int*)&_header[18];
	*_height = *(int*)&_header[22];
	*_depth = *(int*) &_header[28];

	if(*_depth <= 8)
		fread(_colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fIn);
	fread(_buffer, sizeof(unsigned char), CUSTOM_IMG_SIZE, fIn);

	fclose(fIn);
}

// Writing to image
void imgWrite(const char* imgPath, int* _depth, unsigned char* _header, unsigned char* _colorTable, unsigned char* _buffer)
{
	FILE* fOut = fopen(imgPath, "wb");

	fwrite(_header, sizeof(unsigned char), BMP_HEADER_SIZE, fOut);
	if (*_depth <= 8)
		fwrite(_colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fOut);

	fwrite(_buffer, sizeof(unsigned char), CUSTOM_IMG_SIZE, fOut);
	fclose(fOut);
}

int main()
	{
	std::cout << "Hello World" << std::endl;
	int imgWidth, imgHeight, imgDepth;

	unsigned char imgHeaderSize[BMP_HEADER_SIZE];
	unsigned char imgColorTableSize[BMP_COLOR_TABLE_SIZE];
	unsigned char imgBuffer[CUSTOM_IMG_SIZE];

	const char imgName[] = "images/Clip Studio Pain.png";
	const char newImgName[] = "images/Clip Studio Pain_copy.png";

	// Reading from file
	imgReader(imgName, &imgWidth, &imgHeight, &imgDepth, &imgHeaderSize[0], &imgColorTableSize[0], &imgBuffer[0]);

	// Writing to file
	imgWrite(newImgName, &imgDepth, &imgHeaderSize[0], &imgColorTableSize[0], &imgBuffer[0]);


	return 0;
}
