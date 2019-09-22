#include <stdio.h>
#include <math.h>

#include "ppmImageLib.h"
#include "objLib.h"


typedef struct Vec3i
{
	int x;
	int y;
	int z;
} Vec3i;


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


void swapDouble(double * a, double * b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}


void circle(int X, int Y, int R, ppmImg * img, Color * color)
{
	int x = 0;
	int y = R;
	int delta = 1 - 2 * R;
	int error = 0;
	while (y >= 0)
	{
		SetPixelColor(img, X + x, Y + y, color);
		SetPixelColor(img, X + x, Y - y, color);
		SetPixelColor(img, X - x, Y + y, color);
		SetPixelColor(img, X - x, Y - y, color);

		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x + 1;
			continue;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --y + 1;
			continue;
		}
		delta += 2 * (++x - y--);
	}
}


void line(int x0, int y0, int x1, int y1, ppmImg * img, Color * color)
{
	int x, y;

	int deltaX = abs(x1 - x0);
	int deltaY = abs(y1 - y0);
	int error = 0;

	int steepAngle = 0;

	if ( deltaY > deltaX )
	{
		swapInt(&x0, &y0);
		swapInt(&x1, &y1);
		swapInt(&deltaX, &deltaY);
		steepAngle = 1;
	}

	int deltaError = deltaY;

	if (x0 > x1)
	{
		swapInt(&x0, &x1);
		swapInt(&y0, &y1);
	}

	int yDir = ( y1 - y0 ) > 0 ? 1 : -1;


	y = y0;
	for (x = x0; x <= x1; x++)
	{
		/* maximum y value - current y
		 * to make (0;0) in the left bottom corner
		 */
		steepAngle ? SetPixelColor(img, y, x, color) : SetPixelColor(img, x, y, color);

		error += deltaError;
		if ( 2*error >= deltaX)
		{
			y += yDir;
			error -= deltaX;
		}
	}
}


void drawFullTriangle(int x0, int y0, int x1, int y1, int x2, int y2, ppmImg * img, Color * color)
{
	/*
	 * Draw top half of triangle
	 */

	int y;

	if (y1 < y0)
	{
		swapInt(&y0, &y1);
		swapInt(&x0, &x1);
	}
	if (y2 < y0)
	{
		swapInt(&y0, &y2);
		swapInt(&x0, &x2);
	}
	if (y2 < y1)
	{
		swapInt(&y1, &y2);
		swapInt(&x1, &x2);
	}

	double tan1 = (double) (y2 - y1) / (x2 - x1);
	double tan2 = (double) (y2 - y0) / (x2 - x0);

	for (y = y2; y >= y1; y--)
	{
		line((int) (x2 + (y - y2)/tan1), y, (int) (x2 + (y - y2)/tan2), y, img, color);
	}

}



int main(int argc, const char *argv[])
{
	const int imgWidth = 1000;
	const int imgHeight = 1000;
	int i, j;

	int x0, x1, x2, y0, y1, y2;

	int X0 = 200, Y0 = 200;
	int X1 = 700, Y1 = 300;
	int X2 = 400, Y2 = 500;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);
	Color * green = CreateColor(0, 255, 0);
	Color * orange = CreateColor(255, 165, 0);


	ppmImg * imgHead = CreateImg(imgWidth, imgHeight, 255);
	ppmImg * imgTest = CreateImg(imgWidth, imgHeight, 255);
	SetBackgroundColor(imgHead, black);
	SetBackgroundColor(imgTest, black);

	All * triangles = ParseObjFile("./obj/african_head.obj");

	for (i = 0; i < triangles->fCurrent; i++)
	{
		x0 = (int) (triangles->Triangles[i][0].x*imgWidth/2 + imgWidth / 2);
		y0 = (int) (triangles->Triangles[i][0].y*imgHeight/2 + imgHeight / 2);
		x1 = (int) (triangles->Triangles[i][1].x*imgWidth/2 + imgWidth / 2);
		y1 = (int) (triangles->Triangles[i][1].y*imgHeight/2 + imgHeight / 2);
		x2 = (int) (triangles->Triangles[i][2].x*imgWidth/2 + imgWidth / 2);
		y2 = (int) (triangles->Triangles[i][2].y*imgHeight/2 + imgHeight / 2);


		line(x0, y0, x1, y1, imgHead, white);
		line(x0, y0, x2, y2, imgHead, white);
		line(x1, y1, x2, y2, imgHead, white);
	}


	drawFullTriangle(X0, Y0, X1, Y1, X2, Y2, imgTest, orange);


	FlipImageVertically(imgHead);
	FlipImageVertically(imgTest);

	WriteImgToFile(imgHead, "head.ppm");
	WriteImgToFile(imgTest, "test.ppm");

	DeleteImg(imgHead);
	DeleteImg(imgTest);
	
	return 0;
}
