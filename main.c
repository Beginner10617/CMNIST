#include "neuron.h"
#include "string.h"
#include "stdio.h"
#include "time.h"
#include "fileSystem.h"

int main(){
	srand((unsigned int)time(NULL));
	int outs[3] = {4,4,1};
	MLP* mlp = createMLP(3, 3, outs, "MLP");	
	
	Value** testInputs; Value** testOutputs;
	
	float values[] = {
		2.0f, 3.0f,-1.0f,
		3.0f,-1.0f, 0.5f,
	        0.5f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f	
	};
	float gts[] = {1.0f,-1.0f,-1.0f, 1.0f};
	
	testInputs = malloc(sizeof(Value*) * 12);
	testOutputs= malloc(sizeof(Value*) * 4);

	for(int i=0; i<12; i++){
		testInputs[i] = createNewValue(values[i], "x  ");
		snprintf(testInputs[i]->name, sizeof(testInputs[i]->name), "x%d%d", i/3,i%3);
		testInputs[i]->_isparameter = 1;
		if(i%3==0){
			testOutputs[i/3] = createNewValue(gts[i/3], "y ");
			snprintf(testOutputs[i/3]->name, sizeof(testOutputs[i]->name), "y%d", i/3);
			testOutputs[i/3]->_isparameter = 1;
		}
	}
	
	Value*** ypred = malloc(sizeof(Value**) * 4);
	Value** dely = malloc(sizeof(Value*) * 4);
	Value** sqdely = malloc(sizeof(Value*) * 4);
	Value* loss; float step = 0.05f;
	int ctrl = 0;
	while(ctrl != 1){
		printf("------------------\n");
		printf("ypred\t\tygt\t\tdely\n");
		for(int i=0; i<4; i++){
			ypred[i] = evaluateMLP(mlp, testInputs + 3*i);
			dely[i] = sub(testOutputs[i], ypred[i][0]);
			sqdely[i] = mul(dely[i], dely[i]);
			printf("%f\t%f\t%f\n", ypred[i][0]->data, 
					testOutputs[i]->data, dely[i]->data);
		}
		loss = add( add(sqdely[0], sqdely[1]) , add(sqdely[2], sqdely[3]) );
		printf("loss = %f\n", loss->data);
		backPropagate(loss);
		freeComputationTree(loss);
		gradientDescentMLP(mlp, step);
		printf("press 1 to exit ");
		scanf("%d", &ctrl);
	}
	printf("-----------------------\n\n\n\n");
	printmlp(mlp);
	printf("\n\n\n\n");
	saveMLP(mlp, "model.txt");	
	printf("File saved\n");
	return 0;
}
