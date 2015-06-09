#include<math.h>
#define BLOCK  8


int Lhua[BLOCK][BLOCK] ={{16 , 11	,10	,16	,24	,40	,51,	61},
                          {12 ,12,	14	,19	,26	,58,	60,	55},
                          {14	,13	,16	,24	,40	,57,	69,	56},
                           {14 ,17 ,22, 29 ,51 ,87 ,80 ,62 },
                           {18,	22	,37,	56,	68,	109	,103,77},
                           {24,	35,	55	,64,81,	104	,113,	92},
                           {49	,64	,78	,87	,103,121,120,101},
                           {72,	92	,95	,98	,112,100,103,99}};



short round(double a)
{
	if(a >= 0)
	{
		return (short)(a+0.5);
	}
	else
	{
		return (short)(a-0.5);
	}

}

double   Matrix1(short a[BLOCK][BLOCK],int u,int v);


short  Matrix2(double a[BLOCK][BLOCK],int u,int v);



class change
{
    public:
	    change();
		void DCT(short a[BLOCK][BLOCK],double b[BLOCK][BLOCK]);
		void IDCT(double a[BLOCK][BLOCK],short b[BLOCK][BLOCK]);
		void LH(double a[BLOCK][BLOCK],short b[BLOCK][BLOCK],const int c[BLOCK][BLOCK]);
		void LR(short a[BLOCK][BLOCK],double  b[BLOCK][BLOCK],const int c[BLOCK][BLOCK]);
	private:

};


change::change()
{
}


void change::DCT(short a[BLOCK][BLOCK],double  b[BLOCK][BLOCK])
{
	int u,v;
	double tmp1,tmp2;
	for(u = 0;u < BLOCK;u++)
	{
		for(v = 0;v < BLOCK;v++)
		{
			if(u==0)
				tmp1 = 1/sqrt((double)BLOCK);
			else
				tmp1 = sqrt((double)2/BLOCK);
			if(v==0)
				tmp2 = 1/sqrt((double)BLOCK);
			else
				tmp2 = sqrt((double)2/BLOCK);
			b[u][v] = tmp1*tmp2*Matrix1(a,u,v);

		}
	}
}



void change::IDCT(double a[BLOCK][BLOCK],short b[BLOCK][BLOCK])
{
	int u,v;
	for(u = 0;u < BLOCK;u++)
	{
		for(v = 0;v < BLOCK;v++)
		{

			b[u][v] = Matrix2(a,u,v);

		}
	}
	
}



void change::LH(double a[BLOCK][BLOCK],short b[BLOCK][BLOCK],const int c[BLOCK][BLOCK])
{
	int i,j;
	for(i = 0;i < BLOCK;i++)
	{
		for(j = 0;j < BLOCK;j++)
		{
			b[i][j] = (short)(a[i][j]/c[i][j]);			
		}
	}
}


void change::LR(short a[BLOCK][BLOCK],double  b[BLOCK][BLOCK],const int c[BLOCK][BLOCK])
{
	int i,j;
	for(i = 0; i < BLOCK;i++)
	{
		for(j = 0;j < BLOCK;j++)
		{
			b[i][j] = a[i][j]*c[i][j];
		}
	}
}

double Matrix1(short a[BLOCK][BLOCK],int u,int v)
{
	int i,j;
	double SUM = 0.0;
	for(i = 0;i < BLOCK;i++)
	{
		for(j = 0;j < BLOCK; j++)
		{
			SUM = SUM + (double)a[i][j]*cos((2*i+1)*u*3.14/2/BLOCK)*cos((2*j+1)*v*3.14/2/BLOCK);
		}
	}
	return SUM;
}


short  Matrix2(double a[BLOCK][BLOCK],int u,int v)
{
	
	int i,j;
	double tmp1,tmp2;
	double  SUM = 0.0;
	for(i = 0;i < BLOCK;i++)
	{
		for(j = 0;j < BLOCK; j++)
		{
			if(i==0)
				tmp1 = 1/sqrt((double)BLOCK);
			else
				tmp1 = sqrt((double)2/BLOCK);
			if(j==0)
				tmp2 = 1/sqrt((double)BLOCK);
			else
				tmp2 = sqrt((double)2/BLOCK);
			SUM = SUM + tmp1*tmp2*a[i][j]*cos((2*u+1)*i*3.14/2/BLOCK)*cos((2*v+1)*j*3.14/2/BLOCK);
		}
	}
	return (short)SUM;

}