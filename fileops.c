#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileops.h"
#include "sparse.h"
#include "structs.c"

// Big messy mess of a function but it works???
SparseMatrix* matrixFromFile(char* filename, int** dimensions) {
	// Open up the file
	FILE *fp = fopen(filename, "r");
	char buf[1024];
	if (!fp) {
        printf("Can't open file: %s\n",filename);
        return NULL;
    }
	// Figure out how many lines we have
	int lines = 0;
	while(fgets(buf,1024, fp)) {
		lines++;
	}
	// Setup our matrix
	SparseMatrix* R = (SparseMatrix*) malloc(sizeof(SparseMatrix) + lines * sizeof(list*));
	R->size = lines;
	for(int i=0; i<lines; i++) {
		R->listArr[i] = (list*) malloc(sizeof(list*));
	}
	*dimensions = malloc(sizeof(int) * lines);
	// Rewind to start of file
	rewind(fp);
	// Start reading in matrix
	int line_number = 0;
	size_t length;
	list *working_node;
	while(fgets(buf,1024, fp)) {
		// Get rid of \n
		length = strlen(buf);
		if (buf[length - 1] == '\n')
			buf[--length] = '\0';
		// Process line
		char *field = strtok(buf, ",");
		int i;
		int field_number = -1;
		working_node = R->listArr[line_number];
		while(field) {
			field_number++;
			// Field contains the next simplex
			i = atoi(field);
			if(field_number == 0){
				(*dimensions)[line_number] = i;
			} else {
				working_node->value = i;
			}
			field = strtok(NULL, ",");
			// Advance to next node if there's more data
			// But if we were reading dimension then don't bother
			if(field && field_number > 0) {
				working_node->next = (list*) malloc(sizeof(list*));
				working_node = working_node->next;
			} else {
				working_node->next = NULL;
			}
		}
		// If we just processed the dimension then we shouldn't have assigned this memory
		// TODO: Free this memory?
		if(field_number==0) {
			R->listArr[line_number]=NULL;
		}
		fflush(stdout);
		line_number++;
	}
	
	fclose(fp);

	return R;
}
