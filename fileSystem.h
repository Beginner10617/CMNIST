#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "stdio.h"
#include "neuron.h"

void saveMLP(MLP* mlp, char* Fname);
MLP* loadMLP(char* Fname);

#endif
