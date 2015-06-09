f = imread('lena.bmp');
outImg = zeros(size(f));
outImg(:,:,1) = errorDiff(f(:,:,1));
outImg(:,:,2) = errorDiff(f(:,:,2));
outImg(:,:,3) = errorDiff(f(:,:,3));
figure();
imshow(outImg);
a = rgb2gray(f);
outImg1 = errorDiff(a);
figure();
imshow(outImg1);
imwrite(outImg1,'lena1.bmp');
imwrite(outImg,'lenargb.bmp');

