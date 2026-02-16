#ifndef NEURON_UTILS_H
#define NEURON_UTILS_H
#include "stdlib.h"

typedef struct Value Value;

typedef void (*Funcptr)(Value*);

struct Value{
	float data, grad;
	struct Value* _prev[2];	// Only 2 operands
	char op;
	char name[6];
	Funcptr _backward;	
};

Value* createNewValue(float data, char* name);

Value* add(Value* x, Value* y);

Value* mul(Value* x, Value* y);

Value* vtanh(Value* x);

void print(Value* x);

void addBack(Value* x);

void mulBack(Value* x);

void tanhBack(Value* x);

void doNothing(Value* x);

#endif
