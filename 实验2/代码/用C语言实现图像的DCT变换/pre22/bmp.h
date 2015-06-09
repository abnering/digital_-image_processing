//定义基本的获取RGB值得方法


typedef struct
{
	BYTE R;
	BYTE G;
	BYTE B;
} RGB;


class Bmp 
{
	public:		
		Bmp();
		int getcount(BITMAPINFOHEADER infoheader);
		int getwidth(BITMAPINFOHEADER infoheader);
		int getheight(BITMAPINFOHEADER infoheader);
		int getsize(BITMAPINFOHEADER infoheader);		
		BYTE getR(int x,int y,RGB *img,BITMAPINFOHEADER infoheader);
		BYTE getG(int x,int y,RGB *img,BITMAPINFOHEADER infoheader);
		BYTE getB(int x,int y,RGB *img,BITMAPINFOHEADER infoheader);

    private: 
		
			
};

Bmp::Bmp()
{
}


int Bmp::getcount(BITMAPINFOHEADER infoheader)
{
	return infoheader.biBitCount;
}


int Bmp::getwidth(BITMAPINFOHEADER infoheader)
{
	return infoheader.biWidth;
}


int Bmp::getheight(BITMAPINFOHEADER infoheader)
{
	return infoheader.biHeight;
}

int Bmp::getsize(BITMAPINFOHEADER infoheader)
{
	return infoheader.biWidth*infoheader.biHeight;
}

BYTE Bmp::getR(int x,int y,RGB *img,BITMAPINFOHEADER infoheader)
{
	return ((img+(infoheader.biHeight-x)*infoheader.biWidth+y)->R);
}


BYTE Bmp::getG(int x,int y,RGB *img,BITMAPINFOHEADER infoheader)
{
	return ((img+(infoheader.biHeight-x)*infoheader.biWidth+y)->G);
}

BYTE Bmp::getB(int x,int y,RGB *img,BITMAPINFOHEADER infoheader)
{
	return ((img+(infoheader.biHeight-x)*infoheader.biWidth+y)->B);
}


