#include <stdio.h>
#include <stdlib.h>
#include "ppmImageLib.h"


/*****************************************
 * Color part
 ****************************************/

/*
 * Usage:
 *   Color * red = CreateColor(255, 0, 0);
 */
Color * CreateColor(unsigned char red, unsigned char green, unsigned char blue)
{
	Color * color = malloc(sizeof(Color));

	color->r = red;
	color->g = green;
	color->b = blue;

	return color;
}


int ColorCompare(Color * c1, Color * c2)
{
	if ( ( c1->r == c2->r ) && ( c1->g == c2->g ) && ( c1->b == c2->b ) )
		return 1;
	else
		return 0;
}


void DeleteColor(Color * color)
{
	free(color);
}


/*****************************************
 * ppmImage part
 ****************************************/

/*
 * Usage:
 *   ppmImg * img1 = CreateImg(4, 4, 255);
 */
ppmImg * CreateImg(int width, int height, int maxVal)
{
	ppmImg * img = malloc(sizeof(ppmImg));

	img->img = malloc(width * height * sizeof(Color));
	img->imgPtr = &img->img;

	img->width = width;
	img->height = height;
	img->maxVal = maxVal;
	img->format = "P6";

	return img;
}


void SetPixelColor(ppmImg * img, int x, int y, Color * color)
{
	img->img[arr2D(img, x, y)] = *color;
}


/*
 * Return integer as index made from 2D array
 */
int arr2D(ppmImg * img, int x, int y)
{
	return (int) (y*img->width + x);
}


void SetBackgroundColor(ppmImg * img, Color * color)
{
	int i, j;

	for (i = 0; i < img->width; i++)
	{
		for (j = 0; j < img->height; j++)
		{
			SetPixelColor(img, i, j, color);
		}
	}
}


/*
 * Usage:
 *   FlipImageVertically(img);
 */
void FlipImageVertically(ppmImg * img)
{
	Color * currentColor;
	Color * tempColor;
	int x, y;
	int height = img->height;

	for (y = 0; y < height / 2; y++)
	{
		for (x = 0; x < img->width; x++)
		{
			tempColor = GetPixelColor(img, x, height - y - 1);
			currentColor = GetPixelColor(img, x, y);
			SetPixelColor(img, x, y, tempColor);
			SetPixelColor(img, x, height - y - 1, currentColor);
		}
	}
}


/*
 * Usage:
 *   Color * c1 = GetPixelColor(img, x, y);
 */
Color * GetPixelColor(ppmImg * img, int x , int y)
{
	Color * color = malloc(sizeof(Color));

	color->r = img->img[arr2D(img, x, y)].r;
	color->g = img->img[arr2D(img, x, y)].g;
	color->b = img->img[arr2D(img, x, y)].b;

	return color;
}


void WriteImgToFile(ppmImg * img, char * filename)
{
	if (img->format[1] == '3')
	{
		WriteImgToFileASCII(img, filename);

	}
	else if (img->format[1] == '6')
	{
		WriteImgToFileBinary(img, filename);
	}
}


void WriteImgToFileBinary(ppmImg * img, char * fileName)
{
	FILE * imgFile;
	int x, y;

	imgFile = fopen(fileName, "wb");
	fprintf(imgFile, "%s\n%d %d\n%d\n", img->format, img->width, img->height, img->maxVal);

	for (y = 0; y < img->height; y++)
	{
		for (x = 0; x < img->width; x++)
		{
			fprintf(imgFile, "%c%c%c", img->img[arr2D(img, x, y)].r, img->img[arr2D(img, x, y)].g, img->img[arr2D(img, x, y)].b);
		}
	}

	fclose(imgFile);
}


void WriteImgToFileASCII(ppmImg * img, char * fileName)
{
	FILE * imgFile;
	int x, y;

	imgFile = fopen(fileName, "wb");
	fprintf(imgFile, "%s\n%d %d\n%d\n", img->format, img->width, img->height, img->maxVal);

	for (y = 0; y < img->height; y++)
	{
		for (x = 0; x < img->width; x++)
		{
			fprintf(imgFile, "%d %d %d\n", img->img[arr2D(img, x, y)].r, img->img[arr2D(img, x, y)].g, img->img[arr2D(img, x, y)].b);
		}
	}

	fclose(imgFile);
}


void DeleteImg(ppmImg * img)
{
	free(img->img);
	free(img);
}
