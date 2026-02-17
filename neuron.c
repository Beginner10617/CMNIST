#include "neuron.h"

// helper functions
float randomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

Neuron* createNeuron(int dim){
	Neuron* neuron = malloc(sizeof(Neuron));
    	neuron->dimension = dim;
    	neuron->weights = malloc(sizeof(Value*) * dim);
	
	for(int i=0; i<dim; i++){
		neuron->weights[i] = createNewValue(
				randomFloat(),
				"w");
		snprintf(neuron->weights[i]->name, sizeof(neuron->weights[i]->name), "w%d", i);

	}
	neuron->bias = createNewValue(randomFloat(), "b");
	return neuron;
}

Value* evaluate(Neuron *neuron, Value **inputs){

	Value* raw_act = neuron->bias;
	int dim = neuron->dimension;
        for(int i=0; i<dim; i++){
	if(inputs[i]==NULL){
		printf("Input dimension must match neuron\n");
		exit(1);
	}
	Value* wixi = mul(neuron->weights[i], inputs[i]);
        raw_act = add(raw_act, wixi);
    }

    return vtanh(raw_act);
}
