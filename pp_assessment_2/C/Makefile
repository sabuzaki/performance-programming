SRC=MD.c control.c util.c 
OBJ=$(SRC:.c=.o)
CC=icx
#CFLAGS=  -g -O0 -fsanitize-address-use-after-return=runtime -fsanitize=address -no-vec 
#CFLAGS=  -Ofast -ffast-math #-fvectorize #-fsanitize=address -no-vec 
#CFLAGS=  -Ofast -fvectorize -ipo -xHost -qopt-prefetch=3 -fno-alias
#CFLAGS=  -ipo -xHost -funroll-loops -fvectorize
#CFLAGS=  -Ofast -xHost -ipo -flto=full
#CFLAGS=  -Ofast -ipo -xHost -ffreestanding -fjump-tables -fvec-peel-loops -fvec-remainder-loops -mno-gather -mno-scatter
#CFLAGS=  -Ofast -ipo -xHost -ffreestanding -fjump-tables -fvec-peel-loops
#CFLAGS=  -Ofast -ipo -xHost -ffreestanding 
#CFLAGS=  -Ofast -ipo -xHost -fjump-tables -fvec-peel-loops -fvec-remainder-loops -mno-gather -mno-scatter
#CFLAGS=  -Ofast -ipo -xHost -fjump-tables
CFLAGS=  -Ofast -ipo -xHost


all: MD

MD: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm


output.dat: MD input.dat
	./MD


clean:
	rm -f MD $(OBJ) 

$(OBJ) : coord.h Makefile


