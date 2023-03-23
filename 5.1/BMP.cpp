#include"BMP.h"

BMP::BMP() {
	this->fileType[0] = -1;
	this->fileType[1] = -1;
	this->fileSize = -1;
	this->DIBSize = -1;
	this->ImgWidth = -1;
	this->ImgHeight = -1;
	this->ColourPlane = -1;
	this->ColourDepth = -1;
	this->CompressAlg = -1;
	this->PixelArrSize = -1;
	this->HorizontalRes = -1;
	this->VerticalRes = -1;
	this->ColourNum = -1;
	this->ImportantColour = -1;
}


BMP::BMP(const BMP* theFile) {
	this->fileType[0] = theFile->fileType[0];
	this->fileType[1] = theFile->fileType[1];
	this->fileSize = theFile->fileSize;
	this->DIBSize = theFile->DIBSize;
	this->ImgWidth = theFile->ImgWidth;
	this->ImgHeight = theFile->ImgHeight;
	this->ColourPlane = theFile->ColourPlane;
	this->ColourDepth = theFile->ColourDepth;
	this->CompressAlg = theFile->CompressAlg;
	this->PixelArrSize = theFile->PixelArrSize;
	this->HorizontalRes = theFile->HorizontalRes;
	this->VerticalRes = theFile->VerticalRes;
	this->ColourNum = theFile->ColourNum;
	this->ImportantColour = theFile->ImportantColour;

	// Get the pixel 
	size_t width = this->ImgWidth + 4 - (this->ImgWidth % 4);
	this->PArr = new Pixel * [this->ImgHeight];
	if (this->ColourDepth == 24) {
		for (size_t i = this->ImgHeight - 1; i >= 0; i--) {
			*(this->PArr + i) = new Pixel[width];
			for (size_t j = 0; j < this->ImgWidth; j++) {
				(*(this->PArr + i) + j)->Blue = (*(theFile->PArr + i) + j)->Blue;
				(*(this->PArr + i) + j)->Green = (*(theFile->PArr + i) + j)->Green;
				(*(this->PArr + i) + j)->Red = (*(theFile->PArr + i) + j)->Red;
			}
		}
	}

	if (this->ColourDepth == 8) {
		for (size_t i = this->ImgHeight - 1; i >= 0; i--) {
			*(this->PArr + i) = new Pixel[width];
			for (size_t j = 0; j < this->ImgWidth; j++) {
				(*(this->PArr + i) + j)->Blue = (*(theFile->PArr + i) + j)->Blue;
				(*(this->PArr + i) + j)->Green = (*(theFile->PArr + i) + j)->Blue;
				(*(this->PArr + i) + j)->Red = (*(theFile->PArr + i) + j)->Blue;
			}
		}
	}
}

BMP::~BMP() {
	this->fileType[0] = -1;
	this->fileType[1] = -1;
	this->fileSize = -1;
	this->DIBSize = -1;
	this->ImgWidth = -1;
	this->ImgHeight = -1;
	this->ColourPlane = -1;
	this->ColourDepth = -1;
	this->CompressAlg = -1;
	this->PixelArrSize = -1;
	this->HorizontalRes = -1;
	this->VerticalRes = -1;
	this->ColourNum = -1;
	this->ImportantColour = -1;
	for (size_t i = 0; i < this->ImgHeight; i++) {
		delete[] * (this->PArr + i);
	}
	delete[] this->PArr;
}