#include "train_utils.h"
#include "neuron.h"
#include "fileSystem.h"

Value** labelToValueArray(int x){
	if(x<0 || x>9) return NULL;
	Value** out = malloc(sizeof(Value*) * 10);
	for(int i=0; i<10; i++){
		if(i==x)
			out[i] = createNewValue(1.0f,"x");
		else
			out[i] = createNewValue(0.0f, "x");
		sprintf(out[i]->name, "%d", i);
		out[i]->_isparameter = 1;
	}
	return out;
}

Value** imgDataToValueArray(uint8_t *img, int img_sz){
	// convert image data [0,255] into an array
	// of same size with values [0.0f, 1.0f]
	// Use linear scaling
	Value** out = malloc(sizeof(Value*) * img_sz);
	for(int i=0; i<img_sz; i++){
		out[i] = createNewValue(img[i]/127.5f - 1,"x");
		sprintf(out[i]->name, "%d",i);
		out[i]->_isparameter = 1;
	}
	return out;
}

int main(){
	FILE *fptrimg, *fptrlabel;
	printf("loading dataset...\n");
	fptrimg = fopen("dataset/t10k-images-idx3-ubyte", "rb");
	fptrlabel = fopen("dataset/t10k-labels-idx1-ubyte","rb");
	if (fptrimg == NULL || fptrlabel == NULL) {
    		printf("Error opening file!\n");
		return 1;
	}

	MLP* mlp = loadMLP("model.txt");
	if(mlp==NULL){
		printf("Error loading model\n");
		exit(1);
	}

	uint32_t imgheader[4], labelheader[2];
	readImgHeader(imgheader, fptrimg);
	readLabelHeader(labelheader, fptrlabel);
	int image_size = imgheader[2] * imgheader[3];
	uint8_t label = 0;
	uint8_t image[image_size];
	int x=0, y=0, z;
	Value** imageVal; Value** expecOp; Value** ypred;

	while(readNextImage(image, image_size, fptrimg)){
		imageVal = imgDataToValueArray(image, image_size);

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

		expecOp = labelToValueArray(label);
		ypred = evaluateMLP(mlp, imageVal);
		float min = -1.0f;
		for(int abc=0; abc<10; abc++){
			printf("%d : %f\n", abc, ypred[abc]->data);
			if(ypred[abc]->data > min){
				min = ypred[abc]->data;
				z = abc;
			}
		}
		printf("\n");

		printf("Label: %u\nOutput: %d", label, z);
		scanf("Press 0 to exit "); scanf("%d", &y);
		if(y==0) break;

		x++;
		if(x >= imgheader[1]) break;
	}
	printf("%d images read succedfully\n", x);
    	fclose(fptrimg);
	fclose(fptrlabel);
	return 0;
}
