#ifndef NEURON_UTILS_H
#define NEURON_UTILS_H

typedef struct Value{
	float data, grad;
	struct Value* _prev[2];	// Only 2 operands
	char op;
	char name[6];
} Value;

Value* createNewValue(float data, char* name);

Value* add(Value* x, Value* y);

Value* mul(Value* x, Value* y);

Value* vtanh(Value* x);

void print(Value* x);

#endif
