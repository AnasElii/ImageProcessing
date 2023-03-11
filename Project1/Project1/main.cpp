#pragma warning(disable:4996)
#include <iostream>

int main()
{
	std::cout << "Hello World" << std::endl;
	FILE* fIn = fopen("images/cameraman.bmp", "rb");
	FILE* fOut = fopen("images/cameraMan_Copy.bmp", "wb");

	// Reading from file
	if (fIn == (FILE*)0)
		std::cout << "Unable to open Image" << std::endl;

	unsigned char header[54];
	unsigned char colorTable[1024];

	for (unsigned int i = 0; i < 54; i++)
		header[i] = getc(fIn);

	int size = *(int*)&header[2];
	int width = *(int*)&header[18];
	int height = *(int*)&header[22];
	int depth = *(int*) & header[28];

	if (depth <= 8)
		fread(colorTable, sizeof(unsigned char), 1024, fIn);

	// Writing to file
	fwrite(header, sizeof(unsigned char), 54, fOut);
	fwrite(colorTable, sizeof(unsigned char), 1024, fOut);

	char* buff = new char[height * width];
	fread(buff, sizeof(unsigned char), (width * height), fIn);
	fwrite(buff, sizeof(unsigned char), (width * height), fOut);

	fclose(fOut);
	fclose(fIn);

	std::cout << "Size: " << size << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "Depth: " << depth << std::endl;

	return 0;
}