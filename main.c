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
	/*
	Point start;
	Point end;
	*/
	int x0;
	int y0;
	int x1;
	int y1;
} Line;


int main(int argc, const char *argv[])
{
	const int Ximg = 100;
	const int Yimg = 100;
 	int x, y;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);


	Line line1 = {.x0 = 1, .y0 = 50, .x1 = 70, .y1 = 50};

	double tan = (double) (line1.y1 - line1.y0) / (line1.x1 - line1.x0);

	ppmImg * img = CreateImg(Ximg, Yimg, 255);
	SetBackgroundColor(img, white);


	for (x = line1.x0; x <= line1.x1; x++)
	{
		y = round( tan * (x - line1.x0) + line1.y0 );

		SetPixelColor(img, x, Yimg - y, red);
	}

	WriteImgToFile(img, "image.ppm");

	DeleteImg(img);
	
	return 0;
}

