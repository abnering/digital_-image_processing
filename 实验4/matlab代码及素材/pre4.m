disp('请输入文件名')
str=input('please input a book name:','s')
f=imread(str); %读入彩色图像，注意不能使用灰度图像
o=f;                %保留彩色原图
f=rgb2gray(f);     %将彩色图像转换为灰度图像，
f=im2double(f);
figure();
imshow(f);

[m n] = size(f);

y  = f;
%滤波采用低通卷积模板
for i = 2: m-1
    for j = 2:n-1
        y(i,j) = (4*f(i,j) + f(i-1,j-1) + 2*f(i-1,j) + f(i-1,j+1) + 2*f(i,j-1) + 2*f(i,j+1) + f(i+1,j) + 2*f(i+1,j) + f(i+1,j+1))/16;
    end
end
figure();
imshow(y);

%检测边缘采用Sobel算子




q = edge(y,'canny');
imshow(q);
size(q)
d = 3;
M = n*2/3;
z = zeros(1,round(m/d));
num = 0;
i = 1;
A = [];
while(i < m-40)
    count = 0;
    for k = 1:d
        for j = 1:n
            if q(i + k,j) ~= 0
                count = count +1;
            end
        end
    end
    if count > M
       num = num +1 ;
       A = [A,i];
       i = i + 40;
    else
        i = i + 1;
    end
end

X = 0;
l = f;
for i=3:m-2
    for j=3:n-2
        l(i,j)=-f(i-2,j)-f(i-1,j-1)-2*f(i-1,j)-f(i-1,j+1)-f(i,j-2)-2*f(i,j-1)+16*f(i,j)-2*f(i,j+1)-f(i,j+2)-f(i+1,j-1)-2*f(i+1,j)-f(i+1,j+1)-f(i+2,j);%LoG算子
    end
end
figure();
imshow(l);

for  i = 1:A(1)
    for j = 1:n
        if  abs(f(i,j) - 0.45) > 0.2
            X =X +1;
        end
    end
end





if X/A(1)/n > 0.2
    num = num +1;
end
disp('直线所在行数：');
A
disp('书本书目：');
num
        
  
        




