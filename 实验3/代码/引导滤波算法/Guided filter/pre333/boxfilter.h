#include <stdio.h>
#include <stdlib.h>


template <typename T>
void boxfilter(T *b,int h,int w,int r);

template <typename T>
void boxfilter(T *b,int h,int w,int r)
{
	int i,j,k,l;
	double *c = (double  *)malloc(sizeof(double)*h*w);
    //dui  y
	for(j = 0;j< w;j++)
	{
		double sum = 0.0;
		for(i = 0;i < h;i++)
		{
			sum = sum + *(b + i*w+j);
			*(c+i*w+j) = sum;
		}
	}

	for( i = 0;i < r+1;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(b + i*w+j) = *(c+(r+i)*w+j);
		}
	}
	for ( i = r+1;i < h-r;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(b + i*w+j) = *(c+(i+r)*w+j)-*(c+(i-r-1)*w+j);
		}
	}
	for (i = h-r;i<h;i++)
	{
		for(j = 0;j< w;j++)
		{
			*(b + i*w+j) = *(c+(h-1)*w+j) - *(c+(i-r-1)*w+j);
		}
	}

	//dui  x
	for(i = 0;i< h;i++)
	{
		double sum = 0.0;
		for(j = 0;j < w;j++)
		{
			sum = sum + *(b + i*w+j);
			*(c+i*w+j) = sum;
		}
	}

	for(j = 0;j < r+1;j++)
	{
		for(i = 0;i < h;i++)
		{
			*(b + i*w+j) = *(c+i*w+j+r);
			
		}
	
	}

	for(j = r+1;j < w-r;j++)
	{
		for(i = 0;i < h;i++)
		{
			*(b + i*w+j) = *(c + i*w+j+r)-*(c+i*w+j-r-1);
			
		}
	
	}
	for( j = w-r;j < w;j++)
	{
		for(i = 0;i < h;i++)
		{
			*(b + i*w +j) = *(c + i*w + w -1) - *(c+i*w +j-r-1);
			
		}
		
	}
}