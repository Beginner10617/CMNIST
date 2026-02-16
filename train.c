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
	int x=0, y=0;
	while(readNextImage(image, image_size, fptrimg)){
		if(fread(&label, 1, 1, fptrlabel) != 1){
			printf("Error reading label\n");
			break;
		}
/*		for(int a=0; a<imgheader[2]; a++){
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
*/
		x++;
		if(x >= imgheader[1]) break;
	}
	printf("%d images read succedfully\n", x);
    	fclose(fptrimg);
	fclose(fptrlabel);
	return 0;
}
