#include <stdlib.h>
#include <stdio.h>
#include "sparse.h"
#include "fileops.h"

#include "structs.c"

int main(int argc, char** argv) {

	int *dimensions;
	SparseMatrix* R = matrixFromFile(argv[1], &dimensions);
	if(R==NULL) {
		return 0;
	}
	int pairings[R->size];


	/*
	printf("Input:\n");
	for(int i =0; i<R->size; i++) {
		printf("Dim %d:", dimensions[i]);
		if(R->listArr[i] == NULL) {
			printf("NULL\n");
		} else {
			printList(R->listArr[i]);
		}
	}
	*/

	reduceMatrix(R, pairings);
	printf("#REDUCED MATRIX\n");
	for(int i =0; i<R->size; i++) {
		if(R->listArr[i] == NULL) {
			printf("NULL\n");
		} else {
			printList(R->listArr[i]);
		}
	}
	printf("#PAIRINGS\n");
	printPairings(pairings, R->size);

	int *bettiNumbers = computeBettiNumbers(dimensions, pairings, R->size);
	int maxDimension = (dimensions)[R->size - 1];
	printf("#BETTI NUMBERS\n");
	for(int i=0; i<= maxDimension; i++) {
		printf("%d\n", bettiNumbers[i]);
	}

	return 1;
}
