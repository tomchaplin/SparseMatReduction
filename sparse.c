#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "sparse.h"
#include "structs.c"

void reduceMatrix(SparseMatrix *del, int *pairings)
{
	list *L;
	int i;
	for(int j= 0 ; j < del->size ; j++) {
		L = copyList(del->listArr[j]);
		del->listArr[j] = NULL;
		while( L != NULL  ) {
			i = L->value;
			if (del->listArr[i] == NULL ) {
				break;
			}
			L = mergeLists(L, del->listArr[i]);
		}
		if( L != NULL ) {
			del->listArr[i] = copyList(L);
			// sigma_j has killed class born by sigma_i
			pairings[j] = i;
		} else {
			// sigma_j gives birth so we give it pairing -1
			pairings[j] = -1;
		}
	}
}

// The purpose of this function is to merge R into L while leaving L intact.
// We cannot rely on R for parts of L because we are now allowed to change R.
// It is assumed that L and R are decreasing ordered and don't repeat.
list *mergeLists(list *L, list *R) {
	if(R == NULL) {
		// Nothing to merge
		return L;
	} else if (L == NULL) {
		// We don't want to screw up R so we make a copy of R into L
		L = copyList(R);
		return L;
	} else if ( L->value > R->value) {
		// L-> value should be next so we just merge with next and return L
		L->next = mergeLists(L->next, R);
		return L;
	} else if (L-> value == R->value) {
		// We want to ignore these two values
		return mergeLists(L->next, R->next);
	} else {
		// We need to insert the value of R where L currently is
		// So we make a new node with R's valuej
		list *newNode = (list *)malloc(sizeof(list));
		newNode->value = R-> value;
		// Then its next element will be L
		// But then we need to merge L with the rest of R
		newNode->next = mergeLists(L, R->next);
		return newNode;
	}
}

// No idea what is going on here, taken from 
// https://stackoverflow.com/questions/13633182/c-program-to-make-a-second-copy-of-a-linked-list
list *copyList(list *org)
{
	list *new=NULL,**tail = &new;

	for( ;org; org = org->next) {
		*tail = malloc (sizeof **tail );
		(*tail)->value = org->value;
		(*tail)->next = NULL;
		tail = &(*tail)->next;
		}
	return new;
}

void printList(list *L){
	list *current_node = L;
	while( current_node != NULL) {
		printf("%d ", current_node->value);
		current_node = current_node->next;
	}
	printf("\n");
}

void printPairings(int *pairings, int size) {
	for(int i=0; i<size; i++) {
		printf("%d ", pairings[i]);
	}
	printf("\n");
}

int* computeBettiNumbers(int* dimensions, int* pairings, int size) {
	// First we figure out how big a matrix we need to assign
	int maxDimension = (dimensions)[size - 1];
	int *ret = malloc(sizeof(int) * (maxDimension+1));
	for(int i = 0; i<=maxDimension; i++) {
		ret[i] = 0;
	}
	for(int i = 0; i < size ; i++) {
		if( (pairings)[i] == -1 ) {
			ret[ (dimensions)[i] ]++;
		} else {
			ret[ (dimensions)[ (pairings)[i] ]   ]--;
		}
	}
	return ret;
}
