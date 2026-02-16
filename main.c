#include "neuron_utils.h"
#include "string.h"

int main(){
	Value *a = createNewValue(5.0f, "a");
	Value *b = createNewValue(-2.0f,"b");
	Value *c = add(a, b); strcpy(c->name, "c");
	Value *d = vtanh(c);
	print(d);
	print(c);
	return 0;
}
