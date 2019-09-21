#ifndef OBJLIB_H
#define OBJLIB_H

#define BUFFER_LENGTH 255
#define START_VERTEX_COUNT 2
#define START_FACE_COUNT 2
#define MULTIPLIER 2
#define OBJ_STARTS_COUNTING_FROM_ONE 1


struct Vertex
{
	double x;
	double y;
	double z;
} Vertex;


typedef struct Face
{
	int * fL;
} Face;


typedef struct All
{
	int vSize;
	int vCurrent;
	int fSize;
	int fCurrent;
	struct Vertex * V;
	struct Face * F;

	struct Vertex ** Triangles;
} All;


void readFaces(struct Face * f, char * line);

void WriteVertexLine(All * all, char * line);

void WriteFaceLine(All * all, char * line);

void saveVertexesToTriangles(struct Vertex * T, int vertexNumber, struct Vertex * V);

void CreateTriangles(All * all);

All * ParseObjFile(char * fileName);

void DeleteAll(All * all);


#endif //OBJLIB_H
