#ifndef NEURON_H
#define NEURON_H

#include "neuron_utils.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct {
	Value **weights;
	Value * bias;
	int dimension;
	char name[6]; // for debugging
} Neuron;

// Creating a neuron with given dimension and name
Neuron* createNeuron(int dim, char* name);

// Evaluating neuron activation value for given inputs
Value* evaluateNeuron(Neuron* neuron, Value** inputs);

// Freeing allocated memory after backpropagation of non-parameter nodes
void freeComputationTree(Value *root);

// For debugging
void printn(Neuron* neuron);

typedef struct {
	char name[6]; // For debugging
	int num_of_neurons, dim_of_neurons;
	Neuron** neurons;
} Layer;

// Creating a layer with given lengths of input and output, and name
Layer* createLayer(int num_of_inputs, int num_of_outputs, char* name);

// Evaluate layer for a given set of inputs
Value** evaluateLayer(Layer* layer, Value** inputs);

// For debugging
void printl(Layer* layer);
#endif
