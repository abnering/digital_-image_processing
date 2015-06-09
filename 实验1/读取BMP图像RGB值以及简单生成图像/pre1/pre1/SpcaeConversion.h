#include <math.h>

//定义五个结构体
typedef struct
{
	double Y;
	double U;
	double V;
} YUV;

typedef struct
{
	double Y;
	double I;
	double Q;
} YIQ;

typedef struct
{
	double H;
	double S;
	double I;
} HSI;

typedef struct
{
	double H;
	double S;
	double V;

}HSV;

typedef struct  
{
	double X;
	double Y;
	double Z;
}XYZ;

BYTE Findmin(RGB *img);
BYTE Findmax(RGB *img);
double HSV_H(RGB *img);


class SpaceConversion

{
    public:
		SpaceConversion();
		void ToHSI(RGB *img,HSI &img1,int h,int w,BITMAPINFOHEADER infoheader);
		void ToYUV(RGB *img,YUV &img2,int h,int w,BITMAPINFOHEADER infoheader);
		void ToYIQ(RGB *img,YIQ &img3,int h,int w,BITMAPINFOHEADER infoheader);
		void ToHSV(RGB *img,HSV &img4,int h,int w,BITMAPINFOHEADER infoheader);
		void ToXYZ(RGB *img,XYZ &img5,int h,int w,BITMAPINFOHEADER infoheader);
		void HSItoRGB(RGB &img,HSI img1);

};
SpaceConversion::SpaceConversion()
{
}

void SpaceConversion::ToHSI(RGB *img,HSI &img1,int h,int w,BITMAPINFOHEADER infoheader)
{
	int i = infoheader.biHeight-h;
	int j = w;
	BYTE a,b,c;
    a = (img + i*infoheader.biWidth + j) ->R;
	b = (img + i*infoheader.biWidth + j) ->G;
    c = (img + i*infoheader.biWidth + j) ->B;	
	img1.H = acos((float)(2*a - b -c)/2/(sqrt(double((a-b)*(a-b)+(a - c)*(b -c)))));
    img1.S = 1 - (float)3*Findmin(img + i*infoheader.biWidth + j)/(a + b +c);
	img1.I = (a + b +c)/3;
	
}


void SpaceConversion::ToYUV(RGB *img,YUV &img2,int h,int w,BITMAPINFOHEADER infoheader)
{
	int i = infoheader.biHeight-h;
	int j = w;
	BYTE a,b,c;
    a = (img + i*infoheader.biWidth + j) ->R;
	b = (img + i*infoheader.biWidth + j) ->G;
    c = (img + i*infoheader.biWidth + j) ->B;	
	img2.Y = 0.299*a + 0.587*b + 0.144*c;
	img2.U = -0.147*a + (-0.289)*b + 0.436*c;
	img2.V = 0.615*a + (-0.515)*b + (-0.100)*c;

}


void SpaceConversion::ToYIQ(RGB *img,YIQ &img3,int h,int w,BITMAPINFOHEADER infoheader)
{
	int i = infoheader.biHeight-h;
	int j = w;
	BYTE a,b,c;
    a = (img + i*infoheader.biWidth + j) ->R;
	b = (img + i*infoheader.biWidth + j) ->G;
    c = (img + i*infoheader.biWidth + j) ->B;
	img3.Y = 0.299*a + 0.587*b+ 0.144*c;
	img3.I = 0.596*a + (-0.274)*b + (-0.322)*c;
	img3.Q = 0.211*a + (-0.523)*b + 0.312*c;

}


void SpaceConversion::ToHSV(RGB *img,HSV &img4,int h,int w,BITMAPINFOHEADER infoheader)
{
	int i = infoheader.biHeight-h;
	int j = w;
	BYTE a,b,c;
    a = (img + i*infoheader.biWidth + j) ->R;
	b = (img + i*infoheader.biWidth + j) ->G;
    c = (img + i*infoheader.biWidth + j) ->B;
	img4.H = HSV_H(img + i*infoheader.biWidth + j);
	img4.S = (float)(Findmax(img + i*infoheader.biWidth + j)-Findmin(img + i*infoheader.biWidth + j))/Findmax(img + i*infoheader.biWidth + j);
	img4.V = Findmax(img + i*infoheader.biWidth + j);
}


void SpaceConversion::ToXYZ(RGB *img,XYZ &img5,int h,int w,BITMAPINFOHEADER infoheader)
{
	int i = infoheader.biHeight-h;
	int j = w;
	BYTE a,b,c;
    a = (img + i*infoheader.biWidth + j) ->R;
	b = (img + i*infoheader.biWidth + j) ->G;
    c = (img + i*infoheader.biWidth + j) ->B;
    img5.X = 0.490*a + 0.310*b + 0.200*c;
	img5.Y = 0.177*a + 0.813*b + 0.011*c;
	img5.Z = 0.000*a + 0.010*b + 0.990*c;

}

BYTE Findmin(RGB *img)
{
	BYTE min = img->R;
	if(min > img->G)
		min = img->G;
	if(min > img->B)
		min = img->B;
	return min;
}


BYTE Findmax(RGB *img)
{
	BYTE max = img->R;
	if(max < img->G)
		max = img->G;
	if(max < img->B)
		max = img->B;
	return max;
}


double HSV_H(RGB *img)
{
	double v,h,r1,g1,b1;
	double r,g,b;
	r = img->R;
	g = img->G;
	b = img->B;
	v = Findmax(img);
	h = Findmin(img);
	r1 = (v - img->R)/(v - h);
	g1 = (v - img->G)/(v - h);
	b1 = (v - img->B)/(v - h);
	if(v == r && g == h)
		return (5+b1)/6;
	else if(v == r && g != h)
		return (1-g1)/6;
	else if(g == v && b==h)
		return (1+r1)/6;
	else if(g == v && b!=h)
		return (3-b1)/6;
	else if(b == v && r == h)
		return (3+g1)/6;
	else
		return (5-r)/6;
}



void SpaceConversion::HSItoRGB(RGB &img,HSI img1)
{
	double a,b,c;
	a = img1.H;
	b = img1.S;
	c = img1.I;	
	if(a>=0&&a<=2.093)
	{
		img.B = (BYTE)(c*(1-b));
		img.R = (BYTE) (c*(1+b*cos(a)/cos(1.047-a)));
		img.G = (BYTE)(3*c -(img.B+img.R));
	}
	else if(a>=2.093&&a<=4.186)
	{
		img.R = (BYTE)(c*(1-b));
		img.G = (BYTE)(c*(1+b*cos(a-2.093)/cos(3.14-a)));
		img.B = (BYTE)(3*c -(img.R+img.G));
	}
	else
	{
		img.G = (BYTE)(c*(1-b));
		img.B = (BYTE)(c*(1+b*cos(a-4.186)/cos(5.233-a)));
		img.R = (BYTE)(3*c -(img.R+img.B));
	}
	
}

