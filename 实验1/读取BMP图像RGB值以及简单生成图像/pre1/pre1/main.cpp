#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "bmp.h"
#include "SpcaeConversion.h"

int main()
{
	Bmp A;
	SpaceConversion B;
	int size;
	int x,y;
	BYTE r,g,b;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	FILE *fin = fopen("Lena.bmp","rb");
	fread(&fileheader,sizeof(BITMAPFILEHEADER),1,fin);
	fread(&infoheader,sizeof(BITMAPINFOHEADER),1,fin); 		
	printf("图像高度: %d\n",A.getheight(infoheader));
	printf("图像宽度: %d\n",A.getwidth(infoheader));
	printf("图像字节数：%d\n",A.getcount(infoheader));
	size = A.getwidth(infoheader)*A.getheight(infoheader);
	RGB *img = (RGB *)malloc(sizeof(RGB)*size);
	fread(img,sizeof(RGB),size,fin);
	fclose(fin);
	printf("请输入要得到的像素值：x<%d   y < %d\n",A.getheight(infoheader),A.getwidth(infoheader));
	scanf("%d",&x);
	scanf("%d",&y);
	printf("\n");
	r = A.getR(x,y,img,infoheader);
	g = A.getG(x,y,img,infoheader);
	b = A.getB(x,y,img,infoheader);
	printf("像素值R  %d，G  %d，B  %d：\n",r,g,b);

	HSI img1;
	YUV img2;
	YIQ img3;
	HSV img4;
	XYZ img5;
    B.ToHSI(img,img1,x,y,infoheader);
	B.ToYUV(img,img2,x,y,infoheader);
	B.ToYIQ(img,img3,x,y,infoheader);
	B.ToHSV(img,img4,x,y,infoheader);
	B.ToXYZ(img,img5,x,y,infoheader);
	printf("H:%lf   S:%lf      I:%lf\n",img1.H,img1.S,img1.I);
/*	printf("Y:%lf   U:%lf      V:%lf\n",img2.Y,img2.U,img2.V);
	printf("Y:%lf   I:%lf      Q:%lf\n",img3.Y,img3.I,img3.Q);
	printf("H:%lf   S:%lf      V:%lf\n",img4.H,img4.S,img4.V)*/;
	printf("X:%lf   Y:%lf      Z:%lf\n",img5.X,img5.Y,img5.Z);     
    RGB img6;
	B.HSItoRGB(img6,img1);
	printf("R:%d   G:%d     B:%d\n",img6.R,img6.G,img6.B);
	printf("在原图的基础上画一条直线：\n");
	FILE *fin1 = fopen("girl.bmp","rb");
	fread(&fileheader,sizeof(BITMAPFILEHEADER),1,fin1);
	fread(&infoheader,sizeof(BITMAPINFOHEADER),1,fin1); 
	fread(img,sizeof(RGB),size,fin);
	FILE *fp = fopen("result.bmp","w");
	int i,j;
	for(i = 0;i < A.getheight(infoheader);i++)
	{
		for(j = 100;j < 120;j++)
		{
			(img + i*A.getheight(infoheader) + j)->B = 200;
			(img + i*A.getheight(infoheader) + j)->R = 100;
			(img + i*A.getheight(infoheader) + j)->G = 100;
		}
	}
	fwrite(&fileheader,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoheader,sizeof(BITMAPINFOHEADER),1,fp);		
    fwrite(img,sizeof(RGB),size,fp);
	fclose(fin);
	fclose(fp);
	getchar();
	getchar();
	return 0;
}