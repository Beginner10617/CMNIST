#include "neuron_utils.h"
#include "string.h"
#include "stdio.h"
int main(){
	Value *a = createNewValue(5.0f, "a");
	Value *b = createNewValue(-2.0f,"b");
	Value *c = mul(a, b); strcpy(c->name, "c");
	Value *d = createNewValue(10.0f, "d");
	Value *e = add(c, d); strcpy(e->name, "e");
	Value *f = vtanh(e); strcpy(f->name, "f");
	
	print(f);
	print(e);
	print(d);
	print(c);
	print(b);
	print(a);

	f->grad = 1.0f;

	f->_backward(f);
	e->_backward(e);
	d->_backward(d);
	c->_backward(c);
	b->_backward(b);
	a->_backward(a);
	
	printf("grad values are:\n");
	printf("f -> %f\n", f->grad);
	printf("e -> %f\n", e->grad);
	printf("d -> %f\n", d->grad);
	printf("c -> %f\n", c->grad);
	printf("b -> %f\n", b->grad);
	printf("a -> %f\n", a->grad);
	
	return 0;
}
