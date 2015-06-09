girl = input('Please input the picture name \n','s');
f = imread(girl);
f = 255*f;
m = size(f,1);
n = size(f,2);
subplot(1,2,1),imshow(f);title('a.Ô­Ê¼Í¼Ïñ');
T = 10
for k = 1:T
    Img = lpgauss(f);
    Img = uint8(Img);
end



subplot(1,2,2),imshow(Img);title('b.ÂË²¨Æ÷3*3£¬sigma=2');
imwrite(Img,'invgirl.bmp');


