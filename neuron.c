#include "neuron.h"

// helper function
float randomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

Neuron* createNeuron(int dim, char* n){
	Neuron* neuron = malloc(sizeof(Neuron));
    	neuron->dimension = dim;
    	strncpy(neuron->name, n, 4);
	neuron->name[5] = '\0';
	neuron->weights = malloc(sizeof(Value*) * dim);
	
	for(int i=0; i<dim; i++){
		neuron->weights[i] = createNewValue(
				randomFloat(),
				"w");
		snprintf(neuron->weights[i]->name, sizeof(neuron->weights[i]->name), "w%d", i);
		neuron->weights[i]->_isparameter = 1; // Useful when freeing the computaion graph
		printf("neuron weight %s = %f created\n", neuron->weights[i]->name, neuron->weights[i]->data);
	}
	neuron->bias = createNewValue(randomFloat(), "b");
	neuron->bias->_isparameter = 1;
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

void freeComputationTree(Value *root){
	NodeList* nodelist = createNodeList();
	buildTopoSort(nodelist, root);
	for(int i=nodelist->size-1; i>=0; i--){
		if(nodelist->values[i]->_isparameter > 0) continue;
		printf("Removing %s = Value(%f)\n", nodelist->values[i]->name, nodelist->values[i]->data);   
		free(nodelist->values[i]);	
	}
	freeNodeList(nodelist);
}

void printn(Neuron* n){
	printf("-------------------\n");
	printf("node name: %s\n", n->name);
	printf("dimension: %d\n", n->dimension);
	printf("bias: %f\n", n->bias->data);
	printf("-------------------\n");
}
