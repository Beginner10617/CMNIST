#include "neuron.h"
#include "string.h"
#include "stdio.h"
int main(){
	srand((unsigned int)time(NULL));
	Value **x = malloc( 2 * sizeof(Value*));
	x[0] = createNewValue(2, "x1");
	x[1] = createNewValue(1, "x2");
	Neuron *neuron = createNeuron(2);
	Value *z = evaluate(neuron, x);
	print(z);
	return 0;
}
