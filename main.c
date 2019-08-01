#include <stdio.h>
#include <math.h>

#include "ppmImageLib.h"


typedef struct Point
{
	int x;
	int y;
} Point;


int main(int argc, const char *argv[])
{
	const int Ximg = 100;
	const int Yimg = 100;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);

	double tan;
	Point start;
	Point end;

	ppmImg * img = CreateImg(Ximg, Yimg, 255);
	//img->format = "P3";

	SetBackgroundColor(img, white);
	SetPixelColor(img, Ximg, Yimg, black);


	start.x = 1;
	start.y = 4;
	end.x = Ximg-5;
	end.y = 4;

	tan = (double) (end.y - start.y) / (end.x - start.x);

	//fprintf(stdout, "tan = %f\n", tan);

	int x, y;
	for (x = start.x; x <= end.x; x++)
	{
		y = round( tan * (x - start.x) + start.y );

		//fprintf(stdout, "x = %d, y = %d\n", x, y);
		SetPixelColor(img, x, Yimg - y, red);
	}

	WriteImgToFile(img, "image.ppm");

	DeleteImg(img);
	
	return 0;
}

