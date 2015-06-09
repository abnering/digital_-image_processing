f = imread('BoldRedEye.bmp');
f(:,:,1);
f(:,:,2);
f(:,:,3);

g =  f(:,:,1)*0.8 + f(:,:,2)*0.1 +f(:,:,3)*0.1;

m = size(g,1);
n = size(g,2);
imshow(g-f(:,:,1));

p = g-f(:,:,1);
for i = 1:m
    for j = 1:n
        if p(i,j) > 0
            p(i,j) = 200;
        end
    end
end
figure();
imshow(p);
oumiga = 0.06;
row = [];
k = 10;
for i = 1:10:m-k
    count = 0;
    for j = 1:n        
        for k = 1:10
            if p(i+k,j)~= 0
                count=count +1;
            end
        end
    end
    if count > oumiga*n*10
        row = [row,i];      
    end
end
row

for i = 1:size(row)-1
    if row(i+1) - row(i)> 2*10       
        break;
    end
end   

L1 = row(1);
k = size(row,2);
L2  = row(k);

com = [];
for j = 1:10:n - 10
    count = 0;
    for i = row(1):row(k)        
       for k = 1:10
           if p(i,j+k)~= 0
               count =count +1;
           end
       end
    end
    if  count > 0.1*10*(row(k) - row(1))
        com = [com,j];
    end
end
L1
L2
t= 0;
for i = 1:size(com,2)-1
    if com(i+1) - com(i) > 20
        t = i;
    end
end
r = (L2 - L1)/2;
 
num1= [];
for k = com(1)+r:com(t)-r
    count = 0;
    for i = L1:L2
        for j = k -r:k+r
            if (i - L1-r)^2+(j - k)^2 < r^2 
                if p(i,j) == 0
                    count =count +1;
                end
            end
        end
    end
    num1 = [num1,count];
end
num1
max_value = 0;
tag1 = 0;
for i = 1:size(num1,2)
    if max_value < num1(i)
        max_value = num1(i);
        tag1 = i;
    end
end

x1 = L1 + r;
y1 = com(1)+r + tag1;

num2= [];
for k = com(t+1)+r:com(size(com,2))-r
    count = 0;
    for i = L1:L2
        for j = k -r:k+r
            if (i - L1-r)^2+(j - k)^2 < r^2 
                if p(i,j) == 0
                    count =count +1;
                end
            end
        end
    end
    num2 = [num2,count];
end
num2
max_value = 0;
tag2 = 0;
for i = 1:size(num2,2)
    if max_value < num2(i)
        max_value = num2(i);
        tag2 = i;
    end
end
tag2

x2 = L1 + r;
y2 = com(t+1)+r + tag2;
n
x1
y1
x2
y2

FLAG = zeros(m,n);
for i = x1-r:x1+r
    for j = y1-r:y1+r
        if  (i- x1)^2 + (j-y1)^2 <r^2
            if p(i,j) == 0;
                FLAG(i,j) = 1;
                FLAG(i-1,j) = 1;
                FLAG(i,j-1) = 1;
                FLAG(i+1,j) = 1;
                FLAG(i,j+1) = 1;
                p(i,j) = 50;
                p(i+1,j) = 50;
                p(i-1,j) = 50;
                p(i,j-1) = 50;
                p(i,j+1) = 50;
            end
        end
    end
end
r
for i = x2-r:x2+r
    for j = y2-r:y2+r
        if  (i- x2)^2 + (j-y2)^2 <r^2
            if p(i,j) == 0;
                FLAG(i,j) = 1;
                FLAG(i-1,j) = 1;
                FLAG(i,j-1) = 1;
                FLAG(i+1,j) = 1;
                FLAG(i,j+1) = 1;
                p(i,j) = 50;
                p(i+1,j) = 50;
                p(i-1,j) = 50;
                p(i,j-1) = 50;
                p(i,j+1) = 50;
            end
        end
    end
end
            
newf = f;
for i = 1:m
    for j = 1:n
        if FLAG(i,j) == 1
            newf(i,j,1) = (f(i,j,2)+f(i,j,3))/4;
            newf(i,j,2) = (newf(i,j,1)+f(i,j,2))/2;
            newf(i,j,3) = (newf(i,j,1)+f(i,j,3))/2;
        end
    end
end
com
figure();
imshow(newf);
imwrite(newf,'Bold.bmp');



