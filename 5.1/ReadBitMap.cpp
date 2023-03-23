#include"ReadBitMap.h"

#pragma once
#include"BMP.h"
#include<windows.h>

void SaveInformation(FILE* f, BMP* Img) {
	// Get file type
	fread(Img->fileType, sizeof(uint8_t), 2, f);

	// Get file size
	fseek(f, 0x2, SEEK_SET);
	fread(&Img->fileSize, sizeof(Img->fileSize), 1, f);

	// Get pixel array byte offset
	fseek(f, 0xA, SEEK_SET);
	fread(&Img->PArrByOffset, sizeof(Img->PArrByOffset), 1, f);

	// Get DIB size
	fseek(f, 0xE, SEEK_SET);
	fread(&Img->DIBSize, sizeof(Img->DIBSize), 1, f);

	// Get Image width
	fseek(f, 0x12, SEEK_SET);
	fread(&Img->ImgWidth, sizeof(Img->ImgWidth), 1, f);

	// Get Image height
	fseek(f, 0x16, SEEK_SET);
	fread(&Img->ImgHeight, sizeof(Img->ImgHeight), 1, f);

	// Get Colour planes
	fseek(f, 0x1A, SEEK_SET);
	fread(&Img->ColourPlane, sizeof(Img->ColourPlane), 1, f);

	// Get Colour depth
	fseek(f, 0x1C, SEEK_SET);
	fread(&Img->ColourDepth, sizeof(Img->ColourDepth), 1, f);

	// Get Copression Algorithm
	fseek(f, 0x1E, SEEK_SET);
	fread(&Img->CompressAlg, sizeof(Img->CompressAlg), 1, f);

	// Get pixel array size
	fseek(f, 0x22, SEEK_SET);
	fread(&Img->PixelArrSize, sizeof(Img->PixelArrSize), 1, f);

	// Get Horizontal resolution
	fseek(f, 0x26, SEEK_SET);
	fread(&Img->HorizontalRes, sizeof(Img->HorizontalRes), 1, f);

	// Get Vertical resolution
	fseek(f, 0x2A, SEEK_SET);
	fread(&Img->VerticalRes, sizeof(Img->VerticalRes), 1, f);

	// Get Number of colour in colour table
	fseek(f, 0x2E, SEEK_SET);
	fread(&Img->ColourNum, sizeof(Img->ColourNum), 1, f);

	// Get Number of important colours in colour table
	fseek(f, 0x32, SEEK_SET);
	fread(&Img->ImportantColour, sizeof(Img->ImportantColour), 1, f);

	// Get the pixel array
	fseek(f, Img->PArrByOffset, SEEK_SET);
	int width = Img->ImgWidth + 4 - (Img->ImgWidth % 4);
	Img->PArr = new Pixel * [Img->ImgHeight];

	if (Img->ColourDepth == 24) {
		for (int i = Img->ImgHeight - 1; i >= 0; i--) {
			*(Img->PArr + i) = new Pixel[width];
			for (size_t j = 0; j < Img->ImgWidth; j++) {
				uint8_t Blue, Green, Red;
				fread(&Blue, sizeof(uint8_t), 1, f);
				fread(&Green, sizeof(uint8_t), 1, f);
				fread(&Red, sizeof(uint8_t), 1, f);
				(*(Img->PArr + i) + j)->Blue = Blue;
				(*(Img->PArr + i) + j)->Green = Green;
				(*(Img->PArr + i) + j)->Red = Red;
			}
		}
	}

	if (Img->ColourDepth == 8) {
		for (int i = Img->ImgHeight - 1; i >= 0; i--) {
			*(Img->PArr + i) = new Pixel[width];
			for (size_t j = 0; j < Img->ImgWidth; j++) {
				uint8_t Blue;
				fread(&Blue, sizeof(uint8_t), 1, f);
				(*(Img->PArr + i) + j)->Blue = Blue;
				(*(Img->PArr + i) + j)->Green = Blue;
				(*(Img->PArr + i) + j)->Red = Blue;
			}
		}
	}
}

void outputInformation(BMP* Img) {
	cout << "File type:				" << (char)Img->fileType[0] << (char)Img->fileType[1] << endl;
	cout << "File size:				" << Img->fileSize << " (byte)" << endl;
	cout << "Pixel array byte offset:		" << Img->PArrByOffset << endl;
	cout << "DIB size:				" << Img->DIBSize << " (byte)" << endl;
	cout << "Image width:				" << Img->ImgWidth << " (pixels)" << endl;
	cout << "Image height:				" << Img->ImgHeight << " (pixels)" << endl;
	cout << "Colour plane:				" << Img->ColourPlane << endl;
	cout << "Colour depth:				" << Img->ColourDepth << " (bits)" << endl;
	cout << "Compression Algorithm:			" << Img->CompressAlg << endl;
	cout << "Pixel Array size:			" << Img->PixelArrSize << endl;
	cout << "Horizontal Resolution:			" << Img->HorizontalRes << " (pixels/m)" << endl;
	cout << "Vertical Resolution:			" << Img->VerticalRes << " (pixels/m)" << endl;
	cout << "Number of colour:			" << Img->ColourNum << endl;
	cout << "Number of important colour:		" << Img->ImportantColour << endl;
}

void writeInformation(FILE* f, BMP* Img) {
	// HEADER
	// Write file type
	fwrite(Img->fileType, sizeof(Img->fileType), 1, f);

	// Write file size
	fwrite(&Img->fileSize, sizeof(Img->fileSize), 1, f);

	// Write reserved
	char c = 0;
	for (int i = 0; i < 4; i++) {
		fwrite(&c, sizeof(char), 1, f);
	}

	// Write pixel array byte offset
	fwrite(&Img->PArrByOffset, sizeof(Img->PArrByOffset), 1, f);

	// DIB
	// Write DIB size
	fwrite(&Img->DIBSize, sizeof(Img->DIBSize), 1, f);

	// Write Image width
	fwrite(&Img->ImgWidth, sizeof(Img->ImgWidth), 1, f);

	// Write Image height
	fwrite(&Img->ImgHeight, sizeof(Img->ImgHeight), 1, f);

	// Write colour plane
	fwrite(&Img->ColourPlane, sizeof(Img->ColourPlane), 1, f);

	// Write colour depth
	fwrite(&Img->ColourDepth, sizeof(Img->ColourDepth), 1, f);

	// Write copression algorithm
	fwrite(&Img->CompressAlg, sizeof(Img->CompressAlg), 1, f);

	// Write pixel array size
	fwrite(&Img->PixelArrSize, sizeof(Img->PixelArrSize), 1, f);

	// Write Horizontal resolution
	fwrite(&Img->HorizontalRes, sizeof(Img->HorizontalRes), 1, f);

	// Write Vertical resolution
	fwrite(&Img->VerticalRes, sizeof(Img->VerticalRes), 1, f);

	// Write number of colour in colour table
	fwrite(&Img->ColourNum, sizeof(Img->ColourNum), 1, f);

	// Write number of importan colour
	fwrite(&Img->ImportantColour, sizeof(Img->ImportantColour), 1, f);

	// Pixel Array Format
	fseek(f, Img->PArrByOffset, SEEK_SET);
	int width = Img->ImgWidth + 4 - (Img->ImgWidth % 4);
	if (Img->ColourDepth == 24) {
		for (int i = Img->ImgHeight - 1; i >= 0; i--) {
			for (size_t j = 0; j < Img->ImgWidth; j++) {
				uint8_t Blue, Green, Red;
				Blue = (*(Img->PArr + i) + j)->Blue;
				Green = (*(Img->PArr + i) + j)->Green;
				Red = (*(Img->PArr + i) + j)->Red;
				fwrite(&Blue, sizeof(uint8_t), 1, f);
				fwrite(&Green, sizeof(uint8_t), 1, f);
				fwrite(&Red, sizeof(uint8_t), 1, f);
			}
		}
	}

	if (Img->ColourDepth == 8) {
		for (int i = Img->ImgHeight - 1; i >= 0; i--) {
			for (size_t j = 0; j < Img->ImgWidth; j++) {
				uint8_t Blue;
				Blue = (*(Img->PArr + i) + j)->Blue;
				fwrite(&Blue, sizeof(uint8_t), 1, f);
			}
		}
	}
}

bool readFile(const char* fileName, BMP* Img) {
	FILE* f = fopen(fileName, "rb");
	if (f) {
		cout << "File exist!" << endl;
		SaveInformation(f, Img);
		fclose(f);
	}
	else {
		cout << "File doesn't exist!" << endl;
		return false;
	}
	return true;
}

bool writeFile(const char* fileName, BMP* Img) {

	FILE* f = fopen(fileName, "wb");

	if (f) {
		writeInformation(f, Img);
		fclose(f);
		cout << "File close!" << endl;
	}
	else {
		cout << "File don't exist of can't be make!" << endl;
		return false;
	}
	return true;
}

void cutByVer(BMP* SrcImg, BMP* DesImg, int num, int ByVer) {
	DesImg->fileType[0] = SrcImg->fileType[0];
	DesImg->fileType[1] = SrcImg->fileType[1];
	DesImg->DIBSize = SrcImg->DIBSize;
	DesImg->ImgWidth = SrcImg->ImgWidth / ByVer;
	DesImg->ImgHeight = SrcImg->ImgHeight;
	DesImg->PArrByOffset = SrcImg->PArrByOffset;
	DesImg->ColourPlane = SrcImg->ColourPlane;
	DesImg->ColourDepth = SrcImg->ColourDepth;
	DesImg->CompressAlg = SrcImg->CompressAlg;
	DesImg->PixelArrSize = DesImg->ImgHeight * DesImg->ImgWidth * (DesImg->ColourDepth / 8);
	DesImg->fileSize = DesImg->ImgHeight * DesImg->ImgWidth * (DesImg->ColourDepth / 8);
	DesImg->HorizontalRes = SrcImg->HorizontalRes;
	DesImg->VerticalRes = SrcImg->VerticalRes;
	DesImg->ColourNum = SrcImg->ColourNum;
	DesImg->ImportantColour = SrcImg->ImportantColour;

	// Get the pixel 
	int offset =  SrcImg->ImgHeight / ByVer * (num - 1);
	if (ByVer > 2)
		offset *= 2;
	int width = DesImg->ImgWidth + 4 - (DesImg->ImgWidth % 4);
	DesImg->PArr = new Pixel * [DesImg->ImgHeight];
	for (int i = DesImg->ImgHeight - 1; i >= 0; i--) {
		*(DesImg->PArr + i) = new Pixel[width];
		for (size_t j = 0; j < DesImg->ImgWidth; j++) {
			(*(DesImg->PArr + i) + j)->Blue = (*(SrcImg->PArr + i) + j + offset)->Blue;
			(*(DesImg->PArr + i) + j)->Green = (*(SrcImg->PArr + i) + j + offset)->Green;
			(*(DesImg->PArr + i) + j)->Red = (*(SrcImg->PArr + i) + j + offset)->Red;
		}
	}
}

void cutByHor(BMP* SrcImg, BMP* DesImg, int num, int ByHor) {
	DesImg->fileType[0] = SrcImg->fileType[0];
	DesImg->fileType[1] = SrcImg->fileType[1];
	DesImg->DIBSize = SrcImg->DIBSize;
	DesImg->ImgWidth = SrcImg->ImgWidth;
	DesImg->ImgHeight = (SrcImg->ImgHeight / ByHor);
	DesImg->PArrByOffset = SrcImg->PArrByOffset;
	DesImg->ColourPlane = SrcImg->ColourPlane;
	DesImg->ColourDepth = SrcImg->ColourDepth;
	DesImg->CompressAlg = SrcImg->CompressAlg;
	DesImg->PixelArrSize = DesImg->ImgHeight * DesImg->ImgWidth * (DesImg->ColourDepth / 8);
	DesImg->fileSize = DesImg->ImgHeight * DesImg->ImgWidth * (DesImg->ColourDepth / 8);
	DesImg->HorizontalRes = SrcImg->HorizontalRes;
	DesImg->VerticalRes = SrcImg->VerticalRes;
	DesImg->ColourNum = SrcImg->ColourNum;
	DesImg->ImportantColour = SrcImg->ImportantColour;

	// Get the pixel 
	int offset = (num - 1) * SrcImg->ImgHeight / ByHor;
	int width = DesImg->ImgWidth + 4 - (DesImg->ImgWidth % 4);
	DesImg->PArr = new Pixel * [DesImg->ImgHeight];
	for (int i = DesImg->ImgHeight - 1; i >= 0; i--) {
		*(DesImg->PArr + i) = new Pixel[width];
		for (size_t j = 0; j < DesImg->ImgWidth; j++) {
			(*(DesImg->PArr + i) + j)->Blue = (*(SrcImg->PArr + i + offset) + j)->Blue;
			(*(DesImg->PArr + i) + j)->Green = (*(SrcImg->PArr + i + offset) + j)->Green;
			(*(DesImg->PArr + i) + j)->Red = (*(SrcImg->PArr + i + offset) + j)->Red;
		}
	}
}

void cutImg(const char* fileName, BMP* SrcImg, int ByVer, int ByHor) {
	if (SrcImg->ColourDepth == 8) {
		cout << "Cut 8 bit bitmap is not implement yet!" << endl;
		return;
	}

	if (ByVer == 1 && ByHor == 1) {
		return;
	}

	// Cut vertical
	if (ByHor == 1 && ByVer > 1) {
		BMP* DesImg = new BMP[ByVer];
		for (int i = 0; i < ByVer; i++) {
			cutByVer(SrcImg, (DesImg + i), i + 1, ByVer);

			char ch = i + 1 + 48;
			char* NewName = new char[strlen(fileName) + 3 + 1];
			for (int j = 0; j < strlen(fileName); j++) {
				*(NewName + j) = *(fileName + j);
			}
			*(NewName + strlen(fileName) - 4) = '_';
			*(NewName + strlen(fileName) - 3) = ch;
			*(NewName + strlen(fileName) - 2) = '.';
			*(NewName + strlen(fileName) - 1) = 'b';
			*(NewName + strlen(fileName) + 0) = 'm';
			*(NewName + strlen(fileName) + 1) = 'p';
			*(NewName + strlen(fileName) + 2) = '\0';
			writeFile(NewName, DesImg + i);
			delete[] NewName;
			cout << "Deleted new name!" << endl;
		}
		cout << "Success created: " << ByVer << " files" << endl;
		return;
	}

	// Cut Horizotal
	if (ByVer == 1 && ByHor > 1) {
		BMP* DesImg = new BMP[ByHor];
		for (int i = 0; i < ByHor; i++) {
			cutByHor(SrcImg, (DesImg + i), i + 1, ByHor);

			char ch = i + 1 + 48;
			char* NewName = new char[strlen(fileName) + 3 + 1];
			for (int j = 0; j < strlen(fileName); j++) {
				*(NewName + j) = *(fileName + j);
			}
			*(NewName + strlen(fileName) - 4) = '_';
			*(NewName + strlen(fileName) - 3) = ch;
			*(NewName + strlen(fileName) - 2) = '.';
			*(NewName + strlen(fileName) - 1) = 'b';
			*(NewName + strlen(fileName) + 0) = 'm';
			*(NewName + strlen(fileName) + 1) = 'p';
			*(NewName + strlen(fileName) + 2) = '\0';
			writeFile(NewName, DesImg + i);
			delete[] NewName;
			cout << "Deleted new name!" << endl;
		}
		cout << "Success created: " << ByHor << " files" << endl;
		return;
	}
}

void cutImg2(const char* fileName, BMP* SrcImg, int ByVer, int ByHor) {
	// Cut Horizontal and Vertical
	char** File = new char* [ByHor];
	int count = 0;
	BMP* DesImg = new BMP[ByHor];
	for (int i = 0; i < ByHor; i++) {
		cout << "loop: " << i << endl;
		cutByHor(SrcImg, (DesImg + i), i + 1, ByHor);

		char ch = i + 1 + 48;
		char* NewName = new char[strlen(fileName) + 2 + 1];
		for (int j = 0; j < strlen(fileName); j++) {
			*(NewName + j) = *(fileName + j);
		}
		*(NewName + strlen(fileName) - 4) = '_';
		*(NewName + strlen(fileName) - 3) = ch;
		*(NewName + strlen(fileName) - 2) = '.';
		*(NewName + strlen(fileName) - 1) = 'b';
		*(NewName + strlen(fileName) + 0) = 'm';
		*(NewName + strlen(fileName) + 1) = 'p';
		*(NewName + strlen(fileName) + 2) = '\0';
		File[count] = NewName;
		writeFile(NewName, DesImg + i);
		count++;
	}
	BMP Img;
	readFile(File[0], &Img);
	cutImg(File[0], &Img, ByVer, 1);
	readFile(File[1], &Img);
	cutImg(File[1], &Img, ByVer, 1);
}

void outputPixel(BMP* Img) {
	HWND MyConsole = GetConsoleWindow();

	HDC MyHandle = GetDC(MyConsole);

	int pixel = 0;

	for (size_t i = 0; i < Img->ImgHeight; i++) {
		for (size_t j = 0; j < Img->ImgWidth; j++) {
			COLORREF thePixel = RGB(Img->PArr[i][j].Red, Img->PArr[i][j].Green, Img->PArr[i][j].Blue);
			SetPixel(MyHandle, j + 600, i, thePixel);
		}
	}
	ReleaseDC(MyConsole, MyHandle);
	cin.ignore();
}

void outputImg(const char* fileName , int Ver, int Hor) {
	BMP Img;
	if (readFile(fileName, &Img)) {
		outputInformation(&Img);

		cout << "Output pic?(Enter)" << endl;
		cin.ignore();
		cout << endl;
		outputPixel(&Img);

		if (Ver >= 2 && Hor >= 2) {
			cutImg2(fileName, &Img, Ver, Hor);
		}
		cutImg(fileName, &Img, Ver, Hor);
		
	}
}