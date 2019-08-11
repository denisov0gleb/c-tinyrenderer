#ifndef PPMIMAGELIB_H
#define PPMIMAGELIB_H

/*****************************************
 * Color part
 ****************************************/
typedef struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Color;


/*
 * Usage:
 * 		Color * red = CreateColor(255, 0, 0);
 */
Color * CreateColor(unsigned char red, unsigned char green, unsigned char blue);


/*
 * Return 1 if equal colors, and 0 if not
 */
int ColorCompare(Color * c1, Color * c2);


void DeleteColor(Color * color);


/*****************************************
 * ppmImage part
 ****************************************/
typedef struct ppmImg
{
	Color * img;
	Color **imgPtr;
	int width;
	int height;
	int maxVal;
	char * format;
} ppmImg;


/*
 * Usage:
 *   ppmImg * img1 = CreateImg(4, 4, 255);
 */
ppmImg * CreateImg(int width, int height, int maxVal);


/*
 * Return integer as index made from 2D array
 */
int arr2D(ppmImg * img, int x, int y);


void SetPixelColor(ppmImg * img, int x, int y, Color * color);


void SetBackgroundColor(ppmImg * img, Color * color);

/*
 * Usage:
 *   FlipImageVertically(img);
 */
void FlipImageVertically(ppmImg * img);


/*
 * Usage:
 *   Color * c1 = GetPixelColor(img, x, y);
 */
Color * GetPixelColor(ppmImg * img, int x , int y);


void WriteImgToFile(ppmImg * img, char * fileName);

/*
 * For "P3" format
 * Generates human-readable image
 */
void WriteImgToFileASCII(ppmImg * img, char * fileName);


/*
 * For "P6" format
 * Generates PC-readable image
 */
void WriteImgToFileBinary(ppmImg * img, char * fileName);


//int ReadImgFromFile(ppmImg * img, char * fileName);


void DeleteImg(ppmImg * img);


#endif /* PPMIMAGELIB_H */
