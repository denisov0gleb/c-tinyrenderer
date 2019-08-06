#include <stdio.h>
#include <math.h>

#include "ppmImageLib.h"


typedef struct Point
{
	int x;
	int y;
} Point;


typedef struct Line
{
	int x0;
	int y0;
	int x1;
	int y1;
} Line;


void swapInt(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void line(int x0, int y0, int x1, int y1, ppmImg * img, Color * color)
{
	int x, y;

	double tan = (double) (y1 - y0) / (x1 - x0);
	if (x0 > x1)
	{
		swapInt(&x0, &x1);
		swapInt(&y0, &y1);
	}

	for (x = x0; x <= x1; x++)
	{
		y = round( tan * (x - x0) + y0 );

		SetPixelColor(img, x, img->height - y, color);
	}
}


int main(int argc, const char *argv[])
{
	const int imgWidth = 100;
	const int imgHeight = 100;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);


	Line line1 = {.x0 = 30, .y0 = 30, .x1 = 50, .y1 = 70};
	Line line2 = {.x0 = 1, .y0 = 50, .x1 = 70, .y1 = 60};


	ppmImg * img = CreateImg(imgWidth, imgHeight, 255);
	SetBackgroundColor(img, white);

	line(line1.x0, line1.y0, line1.x1, line1.y1, img, red);
	line(line2.x0, line2.y0, line2.x1, line2.y1, img, blue);

	WriteImgToFile(img, "image.ppm");

	DeleteImg(img);
	
	return 0;
}
