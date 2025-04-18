# Makefile for ADI code

#
# C compiler and options for Intel
#
CC=     icc -qopenmp -std=c99
LIB=    -lm

#
# Object files
#
OBJ=    adi.o

#
# Compile
#
adi:   $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIB)

.c.o:
	$(CC) -c $<

#
# Clean out object files and the executable.
#
clean:
	rm *.o adi
