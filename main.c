#include "neuron.h"
#include "string.h"
#include "stdio.h"
#include "time.h"

int main(){
	srand((unsigned int)time(NULL));
	Value **x = malloc( 2 * sizeof(Value*));
	x[0] = createNewValue(2, "x1"); x[0]->_isparameter=1;
	x[1] = createNewValue(1, "x2"); x[1]->_isparameter=1;
	Layer* layer = createLayer(2, 2, "L");	
	Value** z = evaluateLayer(layer, x);
	printl(layer);
	for(int i=0; i<2; i++)
		printn(layer->neurons[i]);
	printv(x[0]);
	printv(x[1]);	
	int n = layer->dim_of_neurons;
	for(int i=0; i<2; i++){
		for(int j=0; j<n; j++){
			printv(layer->neurons[i]->weights[j]);
		}
		printv(layer->neurons[i]->bias);
	}

	printv(z[0]);
	printv(z[1]);

	freeComputationTree(z[0]);
	freeComputationTree(z[1]);
	return 0;
}
