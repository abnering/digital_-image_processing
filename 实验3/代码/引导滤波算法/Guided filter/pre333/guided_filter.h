#include "boxfilter.h"
#include "matrix.h"


void guidedfilter(double *a,double *b,double *c,int h,int w,int r,double e);

void guidedfilter(double *a,double *b,double *c,int h,int w,int r,double e)
{
	int i,j;
	double *N = (double *)malloc(sizeof(double)*h*w);
	double *mean_I = (double *)malloc(sizeof(double)*h*w);
	double *mean_p = (double *)malloc(sizeof(double)*h*w);
	double *mean_IP = (double *)malloc(sizeof(double)*h*w);
	double *cov_IP = (double *)malloc(sizeof(double)*h*w);
	double *mean_II = (double *)malloc(sizeof(double)*h*w);
	double *var_I = (double *)malloc(sizeof(double)*h*w);

	
	double *mean_a = (double *)malloc(sizeof(double)*h*w);
	double *mean_b = (double *)malloc(sizeof(double)*h*w);


	for(i = 0;i < h;i++)
	{
		for(j = 0;j< w;j++)
		{
			*(N + i*w+j) = 1;
		
		}	

	}
	boxfilter(N,h,w,r);

	for(i = 0;i < h;i++)
	{
		for(j = 0;j <w ;j++)
		{
			*(mean_I + i*w + j) =  (*(a + i*w +j));
			*(mean_p +i*w +j) =  (*(b+i*w+j));
			*(mean_IP + i*w +j) = *(mean_I + i*w + j);
			*(mean_II + i*w + j) = *(mean_I + i*w + j);
		}
	}


	matrixFun2(mean_IP,mean_p,h,w);
	matrixFun2(mean_II,mean_I,h,w);
	boxfilter(mean_I,h,w,r);
	boxfilter(mean_p,h,w,r);
	boxfilter(mean_IP,h,w,r);
	boxfilter(mean_II,h,w,r);
	matrixFun1(mean_I,N,h,w);

	matrixFun1(mean_p,N,h,w);
	matrixFun1(mean_IP,N,h,w);

	matrixFun1(mean_II,N,h,w);
	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(cov_IP + i*w +j) = *(mean_IP + i*w +j) - *(mean_I + i*w +j)*(*(mean_p + i*w +j));
		}
	}


	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(var_I + i*w + j) = *(mean_II + i*w +j) - *(mean_I + i*w +j)*(*(mean_I + i*w +j));
		}
	}


	for(i = 0;i < h;i++)
	{
		for( j = 0;j < w;j++)
		{
			*(mean_a + i*w + j) = *(cov_IP + i*w +j)/(*(var_I + i*w + j)+e);
		}
	}

	
	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(mean_b + i*w +j) = *(mean_p + i*w +j) - *(mean_a+i*w+j)* (*((mean_I + i*w +j)));
		}
	}

	boxfilter(mean_a,h,w,r);
	boxfilter(mean_b,h,w,r);
	matrixFun1(mean_a,N,h,w);
	matrixFun1(mean_b,N,h,w);

	

	for( i = 0;i < h;i ++)
	{
		for( j = 0;j  < w;j++)
		{
			*(c + i*w +j ) = (*(mean_a + i*w + j) * (*(a + i*w + j)) +  *(mean_b + i*w + j));
		}
	}



}
