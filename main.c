#include "stdio.h"
#include "stdint.h"
#include "stdlib.h" 

uint32_t swap(uint32_t x) {
    return ((x>>24)&0xff) |
           ((x>>8)&0xff00) |
           ((x<<8)&0xff0000) |
           ((x<<24)&0xff000000);
}

void swapInPlace(uint32_t* arr, int size){
	for(int i=0; i<size; i++){
		*(arr+i) = swap(*(arr+i));
	}
	return;
}

void readImgHeader(uint32_t* head, FILE* ptr){
	if(fread(head, 4, 4, ptr) != 4){
		printf("Error reading the Image header\n");
		fclose(ptr); exit(1);	
	}
	swapInPlace(head, 4);
	printf("-------------------------\n");
	printf("magic number: %d\n", head[0]);
	printf("number of images: %d\n", head[1]);
	printf("number of rows: %d\n", head[2]);
	printf("number of columns: %d\n", head[3]);
	printf("-------------------------\n"); 
	return;
}

void readLabelHeader(uint32_t* head, FILE* ptr){
	if(fread(head, 4, 2, ptr) != 2){
		printf("Error reading the Label header\n");
		fclose(ptr); exit(1);
	}
	swapInPlace(head, 2);
	printf("-------------------------\n");
	printf("magic number: %d\n", head[0]);
	printf("number of images: %d\n", head[1]);
	printf("-------------------------\n");
	return;
}

int readNextImage(uint8_t* img, int img_size, FILE* ptr){
	if(fread(img, 1, img_size, ptr) != img_size){
		if(feof(ptr))
			return 0;
		printf("Error reading images\n");
		return 0;
	}
	return 1;
}

int main(){
	FILE *fptrimg, *fptrlabel;
	
	fptrimg = fopen("dataset/train-images-idx3-ubyte", "rb");
	fptrlabel = fopen("dataset/train-labels-idx1-ubyte","rb");
	if (fptrimg == NULL || fptrlabel == NULL) {
    		printf("Error opening file!\n");
		return 1;
	}
	uint32_t imgheader[4], labelheader[2];
	readImgHeader(imgheader, fptrimg);
	readLabelHeader(labelheader, fptrlabel);
	int image_size = imgheader[2] * imgheader[3];
	uint8_t label = 0;
	uint8_t image[image_size];
	int x=0, y=0;
	while(readNextImage(image, image_size, fptrimg)){
		if(fread(&label, 1, 1, fptrlabel) != 1){
			printf("Error reading label\n");
			break;
		}
		for(int a=0; a<imgheader[2]; a++){
			for(int b=0; b<imgheader[3]; b++){
				if(image[b+a*imgheader[2]]>0)
					printf("@");
				else
					printf(" ");
			}
			printf("\n");
		}
		printf("%u\n", label);
		scanf("%d", &y);
		if(y==0) break;
		x++;
		if(x >= imgheader[1]) break;
	}
	printf("%d images read succedfully\n", x);
    	fclose(fptrimg);
	fclose(fptrlabel);
	return 0;
}
