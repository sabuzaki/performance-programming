SRC=MD.c control.c util.c 
OBJ=$(SRC:.c=.o)
CC=icx
#CFLAGS=  -g -O0 -fsanitize-address-use-after-return=runtime -fsanitize=address -no-vec 
#CFLAGS=  -g -O0 -fsanitize-address-use-after-return=runtime -fsanitize=address -no-vec 
#CFLAGS=  -g -fast
CFLAGS=   -g -Ofast -ipo -xHost


all: MD

MD: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm


output.dat: MD input.dat
	./MD


clean:
	rm -f MD $(OBJ) 

$(OBJ) : coord.h Makefile


