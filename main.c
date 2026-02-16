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

void readHeader(uint32_t* head, FILE* ptr){
	if(fread(head, 4, 4, ptr) != 4){
		printf("Error reading the header\n");
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

int readNextImage(uint32_t* img, int img_size, FILE* ptr){
	if(fread(img, 1, img_size, ptr) != img_size){
		printf("Error reading images\n");
		return 0;
	}
	swapInPlace(img, img_size);
	return 1;
}

int main(){
	FILE *fptr;
	fptr = fopen("dataset/train-images-idx3-ubyte", "rb");
	if (fptr == NULL) {
    		printf("Error opening file!\n");
		return 1;
	}
	uint32_t header[4];
	readHeader(header, fptr);
	int image_size = header[2] * header[3];
	uint32_t image[image_size];
	int x=0;
	while(readNextImage(image, image_size, fptr)){
		x++;
		if(x >= header[1]) break;
	}
	printf("%d images read succedfully\n", x);
    	fclose(fptr);
	return 0;
}
