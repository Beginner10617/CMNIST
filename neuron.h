#ifndef NEURON_H
#define NEURON_H
#include "neuron_utils.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct {
	Value **weights;
	Value * bias;
	int dimension;
} Neuron;

Neuron* createNeuron(int dim);
Value* evaluate(Neuron* neuron, Value** inputs);

#endif
