#pragma once
#include"BMP.h"
#include<windows.h>

void SaveInformation(FILE* f, BMP* Img);

void outputInformation(BMP* Img);

void writeInformation(FILE* f, BMP* Img);

bool readFile(const char* fileName, BMP* Img);

bool writeFile(const char* fileName, BMP* Img);

void cutByVer(BMP* SrcImg, BMP* DesImg, int numer, int denom);

void cutByHor(BMP* SrcImg, BMP* DesImg, int numer, int denom);

void cutImg(const char* fileName, BMP* SrcImg, int ByVer, int ByHor);

void outputPixel(BMP* Img);

void outputImg(const char* fileName, int Ver, int Hor);