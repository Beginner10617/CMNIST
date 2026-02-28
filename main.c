#include "neuron.h"
#include "string.h"
#include "stdio.h"
#include "time.h"

int main(){
	srand((unsigned int)time(NULL));
	Value **x = malloc( 2 * sizeof(Value*));
	x[0] = createNewValue(2, "x1"); x[0]->_isparameter=1;
	x[1] = createNewValue(1, "x2"); x[1]->_isparameter=1;
	int outs[3] = {2,2,1};
	MLP* mlp = createMLP(2, 3, outs, "MLP");	
	Value** z = evaluateMLP(mlp, x);
	printmlp(mlp);
	Layer* layer; Neuron* neuron;
	/*
	for(int i=0; i<mlp->num_of_layers; i++)
	{
		layer = mlp->layers[i];
		printf("\nLayer number %s\n", layer->name);
		for(int j=0; j<layer->num_of_neurons; j++){
			neuron = layer->neurons[j];
			printn(neuron);
			printf("\nNeuron %s\n", neuron->name);
			for(int k=0; k<neuron->dimension; k++){
				printv(neuron->weights[k]);
			}
			printv(neuron->bias);
		}
	}
	*/
	printf("\nInputs:\n");
	printv(x[0]);
	printv(x[1]);	

	printf("\nOutput:\n");
	printv(z[0]);
	printf("\n");
	freeComputationTree(z[0]);
	return 0;
}
