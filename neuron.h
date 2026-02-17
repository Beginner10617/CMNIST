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

Neuron* createNeuron(int dim, char* name);
Value* evaluate(Neuron* neuron, Value** inputs);
void freeComputationTree(Value *root);
void printn(Neuron* neuron);
#endif
