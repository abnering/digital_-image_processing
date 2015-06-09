template <typename T1,typename T2>
void matrixFun1(T1 *a,T2  *b,int h,int w);
template <typename T1,typename T2>
void matrixFun2(T1 *a,T2 *b,int h,int w);

template <typename T1,typename T2>
void matrixFun1(T1 *a,T2 *b,int h,int w)
{
	int i,j;
	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(a+i*w+j) = *(a+i*w+j)/(*(b +i*w+j));
		}
	}
}

template <typename T1,typename T2>
void matrixFun2(T1 *a,T2 *b,int h,int w)
{
	int i,j;
	for(i = 0;i < h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(a+i*w+j) = *(a+i*w+j)*(*(b +i*w+j));
		}
	}
}
