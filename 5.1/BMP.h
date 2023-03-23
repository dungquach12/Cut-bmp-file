#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

struct Pixel {
	uint8_t Blue = 255;
	uint8_t Green = 255;
	uint8_t Red = 255;
};

struct BMP {
	// Header
	uint8_t fileType[2];		// 0x0
	uint32_t fileSize;			// 0x2
	uint32_t PArrByOffset;		// 0xA

	// DIB
	uint32_t DIBSize;			// 0xE	(byte)
	uint32_t ImgWidth;			// 0x12	(pixels)
	uint32_t ImgHeight;			// 0x16	(pixels)
	uint16_t ColourPlane;		// 0x1A	
	uint16_t ColourDepth;		// 0x1C	(1, 4, 8, 16, 24, or 32 bit?)
	uint32_t CompressAlg;		// 0x1E	(0-No, 1-RLE, 3-Huffman, 4-JPEG, 5-PNG)
	uint32_t PixelArrSize;		// 0x22	
	uint32_t HorizontalRes;		// 0x26	(pixels/m)
	uint32_t VerticalRes;		// 0x2A	(pixels/m)
	uint32_t ColourNum;			// 0x2E	
	uint32_t ImportantColour;	// 0x32	

	Pixel** PArr; // Save colour in the Img

// Fuction
	BMP();
	BMP(const BMP* file);
	~BMP();
};

