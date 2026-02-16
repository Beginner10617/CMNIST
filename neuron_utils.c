#include "neuron_utils.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"

Value* createNewValue(float d, char *n){
	Value *z = malloc(sizeof(Value));
	z->data = d;
	z->_prev[0] = NULL;
	z->_prev[1] = NULL;
	z->op = ' ';
	strncpy(z->name, n, 4);
	z->name[5] = '\0';
	z->grad = 0;
	return z;
}

Value* add(Value *x, Value *y){
	Value *z = malloc(sizeof(Value));
	z->data = x->data + y->data;
	z->_prev[0] = x;
        z->_prev[1] = y;
	z->grad = 0.0f;
	z->op = '+';
	return z;
}

Value* mul(Value *x, Value *y){
	Value *z = malloc(sizeof(Value));
	z->data = x->data * y->data;
	z->_prev[0] = x; 
	z->_prev[1] = y;
	z->grad = 0.0f;
	z->op = '*';
	return z;
}

Value* vtanh(Value *x){
	Value *z = malloc(sizeof(Value));
	z->data = tanh(x->data);
	z->_prev[0] = x;
	z->_prev[1] = NULL;
	z->grad = 0.0f;
	z->op = 't';
	return z;
}

void print(Value *x){
	printf("%s", x->name);
	if(x->_prev[1] == NULL && x->_prev[0] == NULL){
		printf(" = %f\n", x->data);
		return;
	}
	else if(x->_prev[1] == NULL){
		printf(" = %f = %c(%s)\n", x->data, x->op, x->_prev[0]->name);
		return;
	}
	printf(" = %f = %s %c %s\n", x->data, x->_prev[0]->name, x->op, x->_prev[1]->name);
}
