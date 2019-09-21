#include <stdio.h>
#include <malloc.h>

#include "objLib.h"


void readFaces(struct Face * f, char * line)
{
	f->fL = malloc(sizeof(int) * 3);
	sscanf(line, "f %d%*[^ ]%d%*[^ ]%d%*[^\n]", &f->fL[0], &f->fL[1], &f->fL[2]);
}


void WriteVertexLine(All * all, char * line)
{

	if (all->vCurrent >= all->vSize)
	{
		all->vSize *= MULTIPLIER;
		all->V = (struct Vertex *) realloc(all->V, sizeof(struct Vertex) * all->vSize);
	}
	sscanf(line, "v %lf %lf %lf", &all->V[all->vCurrent].x, &all->V[all->vCurrent].y, &all->V[all->vCurrent].z);

	++all->vCurrent;
}


void WriteFaceLine(All * all, char * line)
{

	if (all->fCurrent >= all->fSize)
	{
		all->fSize *= MULTIPLIER;
		all->F = (struct Face *) realloc(all->F, sizeof(struct Face) * all->fSize);
	}

	readFaces(&all->F[all->fCurrent], line);

	++all->fCurrent;
}


void CreateTriangles(All * all)
{
	int i, j;

	all->Triangles = malloc(sizeof(struct Vertex *) * all->fCurrent);

	for (i = 0; i < all->fCurrent; i++)
	{
   	all->Triangles[i] = malloc(sizeof(struct Vertex) * 3);
	}

	for (i = 0; i < all->fCurrent; i++)
	{
		for (j = 0; j < 3; j++)
		{
			saveVertexesToTriangles(&all->Triangles[i][j], all->F[i].fL[j] - OBJ_STARTS_COUNTING_FROM_ONE, all->V);
		}
	}
}


void saveVertexesToTriangles(struct Vertex * T, int vertexNumber, struct Vertex * V)
{
	T->x = V[vertexNumber].x;
	T->y = V[vertexNumber].y;
	T->z = V[vertexNumber].z;
}


void DeleteAll(All * all)
{
	free(all->V);
	free(all->F);
	free(all->Triangles);
	free(all);
}


All * ParseObjFile(char * fileName)
{
	char line[BUFFER_LENGTH + 1] = "";
	FILE * file = fopen(fileName, "r");

	All * all = malloc(sizeof(All));
	all->vSize = START_VERTEX_COUNT;
	all->vCurrent = 0;
	all->fSize = START_FACE_COUNT;
	all->fCurrent = 0;
	all->V = malloc(sizeof(struct Vertex) * START_VERTEX_COUNT);
	all->F = malloc(sizeof(struct Face) * START_FACE_COUNT);

	if (file == NULL)
	{
		fprintf(stdout, "No file!\n");
	}
	else
	{
		while(!feof(file))
		{
			if (fgets(line, BUFFER_LENGTH, file))
			{
				switch (line[0])
				{
					case 'v':
						if (line[1] == ' ')
							WriteVertexLine(all, line);

						break;

					case 'f':
						if (line[1] == ' ')
						{
							WriteFaceLine(all, line);
						}
						break;

					default:
						break;
				}
			}
		}

		fclose(file);

		CreateTriangles(all);
	}

	return all;
}
