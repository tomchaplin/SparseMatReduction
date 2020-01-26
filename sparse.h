#include "structs.h"
void reduceMatrix(SparseMatrix *del, int *pairings);
list* mergeLists(list *L, list *R);
list *copyList(list *org);
void printList(list *L);
void printPairings(int *pairings, int size);
int* computeBettiNumbers(int* dimensions, int* pairings, int size);
