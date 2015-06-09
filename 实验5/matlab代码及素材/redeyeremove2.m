f = imread('Red-eye_effect.bmp');
f(:,:,1);
f(:,:,2);
f(:,:,3);

g =  f(:,:,1)*0.9 + f(:,:,2)*0.1 +f(:,:,3)*0.1;

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

imshow(p);

B = 5;
d = 3;
for a = 1:B
    FLAG = zeros(m,n);
    for i = d:m-d
        for j = d:n-d
            count = 0;
           for s = 1:d
               for t =1:d
                   if  p(i+s,j+t) ==0
                       count = count + 1;
                   end
               end
           end
           if count/d/d > 0.5
                FLAG(i,j) = 1;
                FLAG(i-1,j) = 1;
                FLAG(i,j-1) = 1;
                FLAG(i+1,j) = 1;
                FLAG(i,j+1) = 1;
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

figure();
imshow(newf);
size(newf)
newf= im2double(newf);
lastf = newf;
for i = 2:m-2
    for j = 2:n -2        
        lastf(i,j,:) = (4*newf(i,j,:) + newf(i-1,j-1,:) + newf(i-1,j,:)*2+ newf(i-1,j+1,:)+ newf(i,j-1,:)*2 + newf(i,j+1,:)*2 +  newf(i+1,j-1,:)+newf(i+1,j,:)*2 + newf(i+1,j-1,:))/16;  
            
    end
end


        
figure();
imshow(lastf);
imwrite(lastf,'effect.bmp');

           
        


