#include "neuron.h"
#include "string.h"
#include "stdio.h"
int main(){
	srand((unsigned int)time(NULL));
	Value **x = malloc( 2 * sizeof(Value*));
	x[0] = createNewValue(2, "x1"); x[0]->_isparameter=1;
	x[1] = createNewValue(1, "x2"); x[1]->_isparameter=1;
	Neuron *neuron = createNeuron(2, "neuron 1");
	Value *z = evaluate(neuron, x);
	printn(neuron);
	printv(x[0]);
	printv(x[1]);	
	int n = neuron->dimension;
	for(int i=0; i<n; i++){
		printv(neuron->weights[i]);
	}
	printv(neuron->bias);

	printv(z);

	freeComputationTree(z);
	return 0;
}
