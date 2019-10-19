/*
* time: 2019.10.16
* author: fuyuanhao
* descript: read bmp and statistic histogram
* image: lena.bmp
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main(int argc, char** argv)
{
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD bmpColorTable[256];
	BYTE bmpValue[512 * 512];
	FILE *fp;

	fp = fopen("lena.bmp", "rb");
	if (!fp){
		printf("Cann't open the file!\n");
		return 0;
	}

	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(bmpColorTable, sizeof(RGBQUAD), 256, fp);
	fread(bmpValue, 1, 512 * 512, fp);	
	
	//��ͼ��Ҷ�ֵ����һλ������
	int grayValue[512 * 512] = { 0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayValue[i] = bmpColorTable[bmpValue[i]].rgbBlue;
	}

	//ֱ��ͼ
	int grayCount[256] = { 0 };
	double grayFrequency[256] = { 0.0 };
	for (int i = 0; i < 512 * 512; i++)
	{
		grayCount[grayValue[i]]++;
	}
	for (int i = 0; i < 256; i++){
		if (grayCount[i]){
			grayFrequency[i] = grayCount[i] / (512.0*512.0);
			printf("�Ҷ�ֵ%3d Ƶ��Ϊ%6d Ƶ��Ϊ%f\n", i, grayCount[i], grayFrequency[i]);
		}	
	}

	//���ֵ
	int grayMax = 0;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i > grayMax)){
			grayMax = i;
		}
	}
	printf("���Ҷ�ֵΪ%d\n", grayMax);

	//��Сֵ
	int grayMin = 255;
	for (int i = 0; i < 256; i++){
		if (grayCount[i] && (i < grayMin)){
			grayMin = i;
		}
	}
	printf("��С�Ҷ�ֵΪ%d\n", grayMin);

	//���� E(X)
	double grayMean = 0.0;
	for (int i = 0; i < 255; i++){
		if (grayCount[i]){
			grayMean += i * grayFrequency[i];
		}
	}
	printf("����Ϊ%f\n", grayMean);

	//����
	// D(X) = E(X^2) - E(X)^2
	double grayMean2 = 0.0;
	for (int i = 0; i < 255; i++){
		grayMean2 += i * i * grayFrequency[i];
	}
	double grayVariance = grayMean2 - grayMean * grayMean;
	printf("����Ϊ%f\n", grayVariance);

	//��
	double grayEntropy = 0.0;
	for (int i = 0; i < 255; i++){
		if (grayCount[i]){
			grayEntropy += -grayFrequency[i] * log2(grayFrequency[i]);
		}
	}
	printf("ͼ����Ϊ%f\n", grayEntropy);
	
	printf("-----------------------------------λͼ�ļ�ͷ-------------------------------------------\n");
	printf("�ļ���ʶ�� = 0x%X\n", bmpFileHeader.bfType);
	printf("�ļ���С = %d �ֽ�\n", bmpFileHeader.bfSize);
	printf("�����ֶ�1 = %d\n", bmpFileHeader.bfReserved1);
	printf("�����ֶ�2 = %d\n", bmpFileHeader.bfReserved2);
	printf("λͼ���ݵĵ�ַ = %d �ֽ�\n", bmpFileHeader.bfOffBits);

	printf("-----------------------------------λͼ��Ϣͷ-------------------------------------------\n");
	printf("���ṹ��С = %d �ֽ�\n", bmpInfoHeader.biSize);
	printf("λͼ�Ŀ�� = %d\n", bmpInfoHeader.biWidth);
	printf("λͼ�ĸ߶� = %d\n", bmpInfoHeader.biHeight);
	printf("Ŀ���豸λƽ���� = %d \n", bmpInfoHeader.biPlanes);
	printf("λ��� = %d λ\n", bmpInfoHeader.biBitCount);
	printf("ѹ������ = %d\n", bmpInfoHeader.biCompression);
	printf("λͼ�Ĵ�С = %d �ֽ�\n", bmpInfoHeader.biSizeImage);
	printf("Ŀ���豸ˮƽ�ֱ��� = %d \n", bmpInfoHeader.biXPelsPerMeter);
	printf("Ŀ���豸��ֱ�ֱ��� = %d \n", bmpInfoHeader.biYPelsPerMeter);
	printf("ʹ�õ�ɫ���� = %d \n", bmpInfoHeader.biClrUsed);
	printf("��Ҫ��ɫ���� = %d \n", bmpInfoHeader.biClrImportant);

	fclose(fp);
	return 0;

}