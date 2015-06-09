#include "guided_filter.h"
#include "windows.h"


typedef struct
{
	BYTE B;
	BYTE G;
	BYTE R;
} RGB;


int main()
{
	int i,j;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	FILE *fin = fopen("tulips.bmp","rb");
	if(fin == NULL)
	{
		printf("Error open!");
		return 0;
	}
	fread(&fileheader,sizeof(BITMAPFILEHEADER),1,fin);
	fread(&infoheader,sizeof(BITMAPINFOHEADER),1,fin);
	int w,h,size;
	w = infoheader.biWidth;
	h = infoheader.biHeight;
	size = h*w;
	RGB *img = (RGB *)malloc(sizeof(RGB)*size);
	fread(img,sizeof(RGB),size,fin);
	int *B = (int *)malloc(sizeof(int)*size);
	int *G = (int *)malloc(sizeof(int)*size);
	int *R = (int *)malloc(sizeof(int)*size);
	
	

	int *B1 = (int *)malloc(sizeof(int)*size);
    int *G1 = (int *)malloc(sizeof(int)*size);
	int *R1 = (int *)malloc(sizeof(int)*size);
	for(i = 0;i < h;i++)
	{
		for( j = 0;j < w;j ++)
		{
			*(B + i*w + j) = (img + i*w +j) -> B;
			*(G + i*w + j) = (img + i*w +j) -> G;
			*(R + i*w + j) = (img + i*w +j) -> R;

		}
	}
	double r;
	r = 0.01;
	boxfilter(B,h,w,r);
	boxfilter(G,h,w,r);
	boxfilter(R,h,w,r);
	double *N = (double *)malloc(sizeof(double)*h*w);
	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(N+i*w+j) = 1;
		}
	}

	boxfilter(N,h,w,r);
	matrixFun1(B,N,h,w);
	matrixFun1(G,N,h,w);
	matrixFun1(R,N,h,w);
	for(i = 0;i < h;i++)
	{
		for( j = 0;j < w;j++)
		{
			(img+i*w +j)->B = *(B + i*w + j);
			(img + i*w + j)->G = *(G + i*w +j);
			(img + i*w + j)->R = *(R + i*w + j);
		}
	}
	FILE *fout;
    if((fout = fopen("xue11.bmp","wb")) == NULL)
    {
    	 printf("OPEN ERORR!");
    	 return 0;
    }
    else
    {
    	fwrite(&fileheader,sizeof(BITMAPFILEHEADER),1,fout);
	    fwrite(&infoheader,sizeof(BITMAPINFOHEADER),1,fout);
		fwrite(img,sizeof(RGB),size,fout);
	}
	getchar();


	return 0;
}

