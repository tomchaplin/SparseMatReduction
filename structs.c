#include "structs.h"

struct list
{
	int value;
	list *next;
};

struct SparseMatrix
{
	int size;
	list *listArr[];
};

