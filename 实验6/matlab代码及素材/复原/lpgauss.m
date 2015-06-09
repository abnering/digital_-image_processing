function   Img = lpgauss(f)

sig = 2.0;

h=fspecial('gaussian',[7,7],sig);%用预定义的gaussian函数

[m n p]=size(f);

if p==1 %处理灰度图像
    Img=double(f);
    Img=conv2(f,h,'same');%I与h的二维离散卷积
end
if p==3 %处理真彩色
    Img=double(f);
    Img(:,:,1)=conv2(f(:,:,1),h,'same');
    Img(:,:,2)=conv2(f(:,:,2),h,'same');
    Img(:,:,3)=conv2(f(:,:,3),h,'same');
end