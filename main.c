#include "neuron_utils.h"
#include "string.h"
#include "stdio.h"
int main(){
	Value *a = createNewValue(5.0f, "a");
	Value *b = createNewValue(-2.0f,"b");
	Value *c = mul(a, b); strcpy(c->name, "c");
	Value *e = add(c, a); strcpy(e->name, "e");
	Value *f = vtanh(e); strcpy(f->name, "f");
	
	print(f);
	print(e);
	print(c);
	print(b);
	print(a);

	backPropagate(f);	

	printf("grad values are:\n");
	printf("f -> %f\n", f->grad);
	printf("e -> %f\n", e->grad);
	printf("c -> %f\n", c->grad);
	printf("b -> %f\n", b->grad);
	printf("a -> %f\n", a->grad);
	
	return 0;
}
