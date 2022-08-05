
# C Compiler
CC=gcc

build:
	@${CC} -c *.c
	@${CC} -o test *.o

clean:
	@rm -f *.o
	@rm test
