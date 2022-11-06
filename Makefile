
# C Compiler
CC=gcc

build:
	@${CC} -c *.c
	@${CC} -c test/*.c
	@${CC} -o test_options test_options.o opt.o
	@${CC} -o test_commands test_commands.o opt.o

clean:
	@rm -f *.o
	@rm -f test_options test_commands
