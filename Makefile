CC = gcc
CFLAGS = -Wall

OBJ=main.o sparse.o fileops.o

.c.o :
	$(CC) -c $(CFLAGS) $*.c

main:	$(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o main $(LDFLAGS)

# Dependencies

main.o		: fileops.h sparse.h structs.h
sparse.o	: sparse.h structs.h
fileops.o	: fileops.h sparse.h structs.h

# Tidying 
clean:	tidy
	rm -f main *.o *~
	rm -f core *~ .*~ 	

tidy:
	rm -f channel *.o 
