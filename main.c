#include <stdio.h>
#include <math.h>

#include "ppmImageLib.h"
#include "objLib.h"


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


int main(int argc, const char *argv[])
{
	const int imgWidth = 1000;
	const int imgHeight = 1000;
	int i, j;
	int x0, y0;
	int x1, y1;
	int x2, y2;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);
	Color * green = CreateColor(0, 255, 0);


	ppmImg * img = CreateImg(imgWidth, imgHeight, 255);
	SetBackgroundColor(img, black);

	All * triangles = ParseObjFile("./obj/african_head.obj");

	for (i = 0; i < triangles->fCurrent; i++)
	{
		x0 = (int) (triangles->Triangles[i][0].x*imgWidth/2 + imgWidth / 2);
		y0 = (int) (triangles->Triangles[i][0].y*imgHeight/2 + imgHeight / 2);
		x1 = (int) (triangles->Triangles[i][1].x*imgWidth/2 + imgWidth / 2);
		y1 = (int) (triangles->Triangles[i][1].y*imgHeight/2 + imgHeight / 2);
		x2 = (int) (triangles->Triangles[i][2].x*imgWidth/2 + imgWidth / 2);
		y2 = (int) (triangles->Triangles[i][2].y*imgHeight/2 + imgHeight / 2);


		line(x0,y0, x1, y1, img, white);
		line(x0,y0, x2, y2, img, white);
		line(x1,y1, x2, y2, img, white);
	}

	/*
	fprintf(stdout, "Red\n");
	line(10, 10, 10, 50, img, red);
	fprintf(stdout, "Green\n");
	line(10, 10, 50, 50, img, green);
	fprintf(stdout, "Blue\n");
	line(10, 10, 50, 10, img, blue);
	*/

	FlipImageVertically(img);

	WriteImgToFile(img, "image.ppm");

	DeleteImg(img);
	
	return 0;
}
