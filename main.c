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


void circle(int X, int Y, int R, ppmImg * img, Color * color)
{
	int x = 0;
	int y = R;
	int delta = 1 - 2 * R;
	int error = 0;
	while (y >= 0)
	{
		SetPixelColor(img, X + x, img->height - Y - y, color);
		SetPixelColor(img, X + x, img->height - Y + y, color);
		SetPixelColor(img, X - x, img->height - Y - y, color);
		SetPixelColor(img, X - x, img->height - Y + y, color);

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
	int deltaError = deltaY;

	int steepAngle = 0;

	if ( deltaY > deltaX )
	{
		swapInt(&x0, &y0);
		swapInt(&x1, &y1);
		swapInt(&deltaX, &deltaY);
		steepAngle = 1;
	}

	int yDir = ( y1 - y0 ) > 0 ? 1 : -1;

	if (x0 > x1)
	{
		swapInt(&x0, &x1);
		swapInt(&y0, &y1);
	}

	y = y0;

	for (x = x0; x <= x1; x++)
	{
		/* maximum y value - current y
		 * to make (0;0) in the left bottom corner
		 */
		steepAngle ? SetPixelColor(img, img->height - y, x, color) : SetPixelColor(img, x, img->height - y, color);

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
	const int imgWidth = 100;
	const int imgHeight = 100;

	Color * black = CreateColor(0, 0, 0);
	Color * red = CreateColor(255, 0, 0);
	Color * white = CreateColor(255, 255, 255);
	Color * blue = CreateColor(0, 0, 255);
	Color * green = CreateColor(0, 255, 0);


	Line line1 = {.x0 = 30, .y0 = 10, .x1 = 50, .y1 = 70};
	Line line2 = {.x0 = 1, .y0 = 50, .x1 = 70, .y1 = 60};
	Line line3 = {.x0 = 90, .y0 = 40, .x1 = 70, .y1 = 90};


	ppmImg * img = CreateImg(imgWidth, imgHeight, 255);
	SetBackgroundColor(img, white);

	line(line1.x0, line1.y0, line1.x1, line1.y1, img, red);
	line(line2.x0, line2.y0, line2.x1, line2.y1, img, blue);
	line(line3.x0, line3.y0, line3.x1, line3.y1, img, green);

	circle(50, 50, 30, img, black);

	WriteImgToFile(img, "image.ppm");

	DeleteImg(img);
	
	return 0;
}
