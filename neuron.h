#ifndef NEURON_H
#define NEURON_H

#include "neuron_utils.h"

#include "time.h"
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
Value* evaluate(Neuron* neuron, Value** inputs);

// Freeing allocated memory after backpropagation of non-parameter nodes
void freeComputationTree(Value *root);

// For debugging
void printn(Neuron* neuron);
#endif
