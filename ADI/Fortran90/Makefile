# Makefile for ADI code

#
# Fortran compiler and options for Intel
#
FC=     ifort -qopenmp 

#
# Object files
#
OBJ=    adi.o

.SUFFIXES:      .f90 .o
#
# Compile
#
adi:   $(OBJ)
	$(FC) -o $@ $(OBJ) $(LIB)

.f90.o:
	$(FC) -c $<

#
# Clean out object files and the executable.
#
clean:
	rm *.o adi
