#include "train_utils.h"

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
	
	int x=0;
	while(readNextImage(image, image_size, fptrimg)){
		if(fread(&label, 1, 1, fptrlabel) != 1){
			printf("Error reading label\n");
			break;
		}
		// training will be done here
		//
		//
		x++;
		if(x >= imgheader[1]) break;
	}
	
	printf("%d images read succedfully\n", x);
    	
	fclose(fptrimg);
	fclose(fptrlabel);
	
	return 0;
}
