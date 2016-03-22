#include "stdafx.h"
#include "Utils.h"

//根据winRect大小和图像比例，调整显示尺寸
void AdaptImageSizeToWindow(int* inw, int* inh, int imageWidth, int imageHeight, CRect winRect, 
	int xLeftOffset, int xRightoffset, int yTopOffset, int yButtomOffset)
{

	int rw,rh;

	int winWidth=winRect.Width();
	int winHeight=winRect.Height();

	rw=winWidth-xLeftOffset-xRightoffset;
	rh=winHeight-yTopOffset-yButtomOffset;

	int w=imageWidth;
	int h=imageHeight;

	if((double)rw/(double)rh<=(double)w/(double)h)
	{
		rh=(int)((double)rw*(double)h/(double)w+0.5f);
	}
	else
	{
		rw=(int)((double)rh*(double)w/(double)h+0.5f);
	}

	*inw=rw;
	*inh=rh;
}

void DrawImgToCtrlsAdaptively(HDC imgDC, IplImage* img, CRect rect)
{
	//图像大小
	int imgWidth = img->width;
	int imgHeight = img->height;
	//rect.right-=5;
	//目标大小
	int targetWidth, targetHeight;
	AdaptImageSizeToWindow(&targetWidth,&targetHeight,imgWidth,imgHeight,rect);

	CRect dRect(0,0,targetWidth,targetHeight);
	DrawImgToCtrls(imgDC, img, dRect);
}

void DrawImgToCtrls(HDC imgDC, IplImage* img, CRect rect)
{
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(imgDC,&rect);
	cimg.Destroy();
}



void DrawCross(const CvPoint2D32f pt, int len, IplImage* image, int r, int g, int b)
{
	CvPoint pt1, pt2;
	pt1 = cvPoint( cvRound( pt.x - len/2), cvRound( pt.y ) );
	pt2 = cvPoint( cvRound( pt.x + len/2), cvRound( pt.y ) );
	cvLine(image, pt1, pt2, CV_RGB(r,g,b), 2, 8, 0 );

	pt1 = cvPoint( cvRound( pt.x ), cvRound( pt.y - len/2) );
	pt2 = cvPoint( cvRound( pt.x ), cvRound( pt.y + len/2) );
	cvLine(image, pt1, pt2, CV_RGB(r,g,b), 2, 8, 0 );
}


void DataCopy2D(unsigned char* tar, unsigned char* orgin, int w, int h, int bytes, int stride)
{
	if(tar==NULL || orgin==NULL) return;
	for(int i=0;i<h;i++)
	{
		memcpy(tar+i*w*bytes,orgin+i*stride,w*bytes);
	}
}

void IplImageDataCopy(unsigned char* tar, IplImage* img)
{
	int h=img->height;
	int w=img->width;
	int stride=img->widthStep;
	int bytes=img->widthStep/w;
	char* data=img->imageData;

	DataCopy2D(tar,(unsigned char*)data,w,h,bytes,stride);
}