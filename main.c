#include "stdio.h"
#include "stdint.h"

uint32_t swap(uint32_t x) {
    return ((x>>24)&0xff) |
           ((x>>8)&0xff00) |
           ((x<<8)&0xff0000) |
           ((x<<24)&0xff000000);
}

int main(){
	FILE *fptr; int x=1;
	fptr = fopen("dataset/train-images-idx3-ubyte", "rb");
	if (fptr == NULL) {
    		printf("Error opening file!");
		return 1;
	}
	uint32_t bytes[4];
    	while (fread(bytes, 4, 4, fptr) == 4) {
        	printf("n1: %u\tn2: %u\tn3: %u\tn4: %u\n",
			swap(bytes[0]), swap(bytes[1]),
			swap(bytes[2]), swap(bytes[3]));
		scanf("%d", &x);
		if(x==0) break;
	}

    	fclose(fptr);
	return 0;
}
