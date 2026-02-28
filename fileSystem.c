#include "fileSystem.h"
#include "stdlib.h"

void saveMLP(MLP* mlp, char* Fname){
	FILE *file;	
	file = fopen(Fname, "w");
	if (file == NULL){
		printf("Error opening file %s\n", Fname);
		exit(1);
	}
	fprintf(file, "%s\n", mlp->name);
	fprintf(file, "%d\n%d\n%d\n",mlp->num_of_outputs,
		mlp->num_of_inputs, mlp->num_of_layers);
	
	for(int i=0; i<mlp->num_of_layers; i++){
		fprintf(file, "%s\n", mlp->layers[i]->name);
		fprintf(file, "%d\n%d\n", mlp->layers[i]->num_of_neurons,
				mlp->layers[i]->dim_of_neurons);
		for(int j=0; j<mlp->layers[i]->num_of_neurons; j++){
			fprintf(file, "%s\n", mlp->layers[i]->neurons[j]->name);
			fprintf(file, "%d\n", mlp->layers[i]->neurons[j]->dimension);
			fprintf(file, "%f\n", mlp->layers[i]->neurons[j]->bias->data);
			for(int k=0; k<mlp->layers[i]->neurons[j]->dimension; k++){
				fprintf(file, "%f\n", mlp->layers[i]->neurons[j]->weights[k]->data);
			}
		}
	}
	fclose(file);
}

MLP* loadMLP(char* Fname){
	char line[20];
	FILE *file;
	file = fopen(Fname, "r");
	if(file == NULL){
		printf("Error opening file %s\n", Fname);
		exit(1);
	}	
	MLP* z = malloc(sizeof(MLP));
	
	if(fgets(line, sizeof(line), file) == NULL){printf("Error reading file\n"); exit(1);}
	return NULL;
}
