function [outImg] = errorDiff(a)
a = double(a);
m = size(a,1);
n = size(a,2);

T = 127.5;
y = a;
error = 0;

y = [127.5*ones(m,2) y 127.5*ones(m,2); 127.5*ones(2,n+4)];
z = y;

for i = 1:m
    for j = 3:n+2
        z(i,j) = 255*(y(i,j) >=T);
        error = y(i,j) - z(i,j);
        
        y(i,j+2) = 5/48*error + y(i,j+2);
        y(i,j+1) = 7/48*error + y(i,j+1);
        
        y(i+1,j+2) = 3/48*error + y(i+1,j+2);
        y(i+1,j+1) = 5/48*error + y(i+1,j+1);
        y(i+1,j)   = 7/48*error + y(i+1,j);
        y(i+1,j-1) = 5/48*error + y(i+1,j-1);
        y(i+1,j-2) = 3/48*error + y(i+1,j-2);
        
        y(i+2,j+2) = 1/48*error + y(i+2,j+2);
        y(i+2,j+1) = 3/48*error + y(i+2,j+1);
        y(i+2,j) = 5/48*error + y(i+2,j);
        y(i+2,j-1) = 3/48*error + y(i+2,j-1);
        y(i+2,j-2) = 1/48 *error + y(i+2,j-2);
    end
end
outImg = z(1:m,3:n+2);
outImg = im2bw(uint8(outImg));