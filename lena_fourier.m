IMG = imread('lena24.bmp');

%ȡRGB���ж�ά���ٸ���Ҷ�任
R = fft2(IMG(:,:,1));
G = fft2(IMG(:,:,2));
B = fft2(IMG(:,:,3));

%������Ļ����
Rimg = fftshift(R);
Gimg = fftshift(G);
Bimg = fftshift(B);

%ȡ��������Ҷ������
FR = log10(abs(Rimg)+1);
FG = log10(abs(Gimg)+1);
FB = log10(abs(Bimg)+1);

%ȡ���Ը���Ҷ��λ��
AR = angle(Rimg);
AG = angle(Gimg);
AB = angle(Bimg);

%����ԭʼͼ��
subplot(2,4,1);imshow(IMG);title('ԭʼͼ��');
%����RGB����Ƶ��ͼ��
subplot(2,4,2);imshow(FR,[]);title('R ��ֵƵ��');
subplot(2,4,3);imshow(FG,[]);title('G ��ֵƵ��');
subplot(2,4,4);imshow(FB,[]);title('B ��ֵƵ��');
%����RGB��λƵ��ͼ��
subplot(2,4,6);imshow(AR);title('R ��λƵ��');
subplot(2,4,7);imshow(AG);title('G ��λƵ��');
subplot(2,4,8);imshow(AB);title('B ��λƵ��');

%��ʼ��任
subplot(2,4,5);
%��任��ԭRGBͼ��
fr = real(ifft2(abs(R).*exp(i*angle(R))))/255.0;
fg = real(ifft2(abs(G).*exp(i*angle(G))))/255.0;
fb = real(ifft2(abs(B).*exp(i*angle(B))))/255.0;
%���RGB����ͼ
img(:,:,1) = fr;
img(:,:,2) = fg;
img(:,:,3) = fb;

imshow(img);
title('��ԭͼ��');