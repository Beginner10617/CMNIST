#include "train_utils.h"
#include "fileSystem.h"
#include "time.h"
 #include "stdio.h"
#include "neuron.h"

Value** labelToValueArray(int x){
	// convert x into an array size 10
	// having 1.0f at index x, 0.0f elsewhere
	return NULL;
};

Value** imgDataToValueArray(uint8_t *img, int img_sz){
	// convert image data [0,255] into an array
	// of same size with values [-1.0f, 1.0f]
	// Use linear scaling
	return NULL;
}

void train(){
	srand((unsigned int)time(NULL));
	
	FILE *fptrimg, *fptrlabel;
	
	fptrimg = fopen("dataset/train-images-idx3-ubyte", "rb");
	fptrlabel = fopen("dataset/train-labels-idx1-ubyte","rb");
	
	if (fptrimg == NULL || fptrlabel == NULL) {
    		printf("Error opening file!\n");
		return ;
	}
	
	uint32_t imgheader[4], labelheader[2];
	readImgHeader(imgheader, fptrimg);
	readLabelHeader(labelheader, fptrlabel);
	
	int image_size = imgheader[2] * imgheader[3];
	uint8_t label = 0;
	Value*** ground_truth = malloc(sizeof(Value**) * labelheader[1]);
	Value*** img_inputs = malloc(sizeof(Value**) * imgheader[1]);
	uint8_t image[image_size];
		
	for(int i=0; i<imgheader[1]; i++){
		if(fread(&label, 1, 1, fptrlabel) != 1){
			printf("Error reading label\n");
			break;
		}
		
		if(!readNextImage(image, image_size, fptrimg)) break;
		// load data to Value ground_truths[i]->{_, _, _, _, _, _, _, _, _, _}, 
		// img_inputs[i] : convert [0,256) -> [-1,1], 
		
	}
    
	MLP* mlp = loadMLP("model.txt");
	int outputs[] = {128,128,10};
	if(mlp==NULL){
		printf("model not found, creating new...\n");
		mlp = createMLP(image_size, 3, outputs, "ADAM");
	}

	Value*** ypred = malloc(sizeof(Value**) * labelheader[1]);
	Value***  dely = malloc(sizeof(Value**) * labelheader[1]);
	Value*** sqdely= malloc(sizeof(Value**) * labelheader[1]);

		
	fclose(fptrimg);
	fclose(fptrlabel);
	saveMLP(mlp, "model.txt");
}

int main(){
	train();
	return 0;
}
