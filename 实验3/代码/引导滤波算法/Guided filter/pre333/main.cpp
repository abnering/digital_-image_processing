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
	FILE *fin = fopen("HIT.bmp","rb");
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
	double *B = (double *)malloc(sizeof(double)*size);
	double *G = (double *)malloc(sizeof(double)*size);
	double *R = (double *)malloc(sizeof(double)*size);
	
	

	double *B1 = (double *)malloc(sizeof(double)*size);
	double *G1 = (double *)malloc(sizeof(double)*size);
	double *R1 = (double *)malloc(sizeof(double)*size);
	for(i = 0;i < h;i++)
	{
		for( j = 0;j < w;j ++)
		{
			*(B + i*w + j) = (double)(((img + i*w +j) -> B))/255;
			*(G + i*w + j) = (double)((img + i*w +j) -> G)/255;
			*(R + i*w + j) = (double)((img + i*w +j) -> R)/255;

			*(B1 + i*w + j) = *(B + i*w + j);
			*(G1 + i*w + j) = *(G + i*w + j);
			*(R1 + i*w + j) = *(R + i*w + j);
		}
	}


	double *B2 = (double *)malloc(sizeof(double)*size);
	double *G2 = (double *)malloc(sizeof(double)*size);
	double *R2 = (double *)malloc(sizeof(double)*size);

	guidedfilter(B,B1,B2,h,w,16,0.01);
	guidedfilter(G,G1,G2,h,w,16,0.01);
	guidedfilter(R,R1,R2,h,w,16,0.01);


	//for(i = 0; i < h;i++)
	//{
	//	for(j = 0;j < w;j++)
	//	{
	//		*(B2 + i*w + j) = ((double)((((img + i*w +j) -> B))/255 - *(B2 + i*w +j))*4 + *(B2 + i*w +j));
	//		*(G2 + i*w + j) = (((double)((img + i*w +j) -> G)/255 -   *(G2 + i*w +j))*4 + *(G2 + i*w +j));
	//		*(R2 + i*w + j) =(((double)((img + i*w +j) -> R)/255 -   *(R2 + i*w +j))*4 + *(R2 + i*w +j));
	//	}
	//}
	for(i = 0; i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(B2 + i*w + j) =  *(B2 + i*w +j);
			*(G2 + i*w + j) =  *(G2 + i*w +j);
			*(R2 + i*w + j) =  *(R2 + i*w +j);
		}
	}

	BYTE *B3 = (BYTE *)malloc(sizeof(BYTE)*size);
	BYTE *G3 = (BYTE *)malloc(sizeof(BYTE)*size);
	BYTE *R3 = (BYTE *)malloc(sizeof(BYTE)*size);
	for(i = 0;i < h;i++)
	{
		for( j = 0;j < w;j++)
		{
			if   (*(B2+i*w+j)< 0)
				*(B3+i*w+j) = 0;
			if   (*(G2+i*w+j)< 0)
				*(G3 + i*w +j) = 0;
			if  (*(R2+i*w+j)< 0)
				*(R3 + i*w +j) = 0;

			if   (*(B2+i*w+j)> 1)
				 *(B3+i*w+j) = 255;
			if   (*(G2+i*w+j)>1)
				*(G3 + i*w +j) = 255;
			if  (*(R2+i*w+j)>1)
				*(R3 + i*w +j) = 255;

			if  (*(B2+i*w+j)>=0&&*(B2+i*w+j)<=1)
				*(B3+i*w+j) =  (BYTE)((*(B2+i*w+j))*255);
			if  (*(G2+i*w+j)>=0&&*(G2+i*w+j)<=1)
				*(G3+i*w+j) =  (BYTE)((*(G2+i*w+j))*255);
			if  (*(R2+i*w+j)>=0&&*(R2+i*w+j)<=1)
				*(R3+i*w+j) =  (BYTE)((*(R2+i*w+j))*255);

			(img + i*w+j)->R = *(R3+i*w+j);
			(img + i*w +j)->G = *(G3+i*w+j);
			(img + i*w +j) ->B = *(B3+i*w+j);

		}
	}

	FILE *fout;
    if((fout = fopen("xue111.bmp","wb")) == NULL)
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
	fclose(fin);
	fclose(fout);
	printf("生成图像成功，请查看，在同目录下：\n");
	getchar();


	return 0;
}