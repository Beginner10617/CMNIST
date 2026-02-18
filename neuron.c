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

Value* evaluateNeuron(Neuron *neuron, Value **inputs){

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
	printf("neuron name: %s\n", n->name);
	printf("dimension: %d\n", n->dimension);
	printf("bias: %f\n", n->bias->data);
	printf("-------------------\n");
}

Layer* createLayer(int num_of_inputs, int num_of_outputs, char* n){
	Layer* layer = malloc(sizeof(Layer));
	strncpy(layer->name, n, 4);      
	layer->name[5] = '\0';
	layer->num_of_neurons = num_of_outputs;
	layer->dim_of_neurons = num_of_inputs;
	layer->neurons = malloc(sizeof(Neuron*) * num_of_outputs);

	for(int i=0; i<num_of_outputs; i++){
		layer->neurons[i] = createNeuron(num_of_inputs, "n");
		snprintf(layer->neurons[i]->name, sizeof(layer->neurons[i]->name), "n%d", i);
	}
	return layer;
}

Value** evaluateLayer(Layer* layer, Value** inputs){
	Value** output = malloc(sizeof(Value*) * layer->num_of_neurons);
	for(int i=0; i<layer->num_of_neurons; i++){
		output[i] = evaluateNeuron(layer->neurons[i], inputs);
	}
	return output;
}

void printl(Layer* layer){
	printf("-------------------\n");  
	printf("layer name: %s\n", layer->name);
	printf("%d neurons, \neach taking %d inputs\n", layer->num_of_neurons, layer->dim_of_neurons);
	printf("-------------------\n");
}
