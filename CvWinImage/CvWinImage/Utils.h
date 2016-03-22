#pragma once

#include "stdafx.h"
#include "opencv\cv.h"
#include "CvvImage.h"

#include <windows.h> 
#include <wincon.h> 
#include <stdio.h> 
#include <nb30.h>


//ИљОн
void AdaptImageSizeToWindow(int* inw, int* inh, int imageWidth, int imageHeight, CRect winRect, 
	int xLeftOffset=0, int xRightoffset=0, int yTopOffset=0, int yButtomOffset=0);

void DrawImgToCtrlsAdaptively(HDC imgDC, IplImage* img, CRect rect);

void DrawImgToCtrls(HDC imgDC, IplImage* img, CRect rect);

void DrawCross(const CvPoint2D32f pt, int len, IplImage* image, int r=255, int g=0, int b=255);

void DataCopy2D(unsigned char* tar, unsigned char* orgin, int w, int h, int bytes, int stride);

void IplImageDataCopy(unsigned char* tar, IplImage* img);