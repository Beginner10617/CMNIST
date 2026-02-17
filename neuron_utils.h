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
	// For topo-sort	
	int visited;
	// Fpr computation tree
	int _isparameter;
};

// For topo-sort
typedef struct {
	Value** values;
	int size, cap;
}NodeList;

NodeList* createNodeList();
void append(NodeList* nodelist, Value* newValue);
void buildTopoSort(NodeList *nodelist, Value* v);
void resetVisited(NodeList *nodelist);
void freeNodeList(NodeList* nodelist);

// Initialising a value
Value* createNewValue(float data, char* name);

// Operations on value
Value* add(Value* x, Value* y);
Value* mul(Value* x, Value* y);
Value* vtanh(Value* x);

void printv(Value* x);

// For back-propagation
void addBack(Value* x);
void mulBack(Value* x);
void tanhBack(Value* x);
void doNothing(Value* x);

void backPropagate(Value* x);

#endif
