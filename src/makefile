main:			main.o  binary_tree.o  binary_tree_print.o  error.o  stack.o  process_input.o
			gcc -Wall -ansi		main.o  binary_tree.o  binary_tree_print.o  error.o  stack.o  process_input.o		-o main


main.o:			main.c  binary_tree.h  error.h  stack.h  process_input.h
			gcc -c -Wall -ansi	main.c				-o main.o


binary_tree.o:		binary_tree.c  binary_tree.h  error.h
			gcc -c -Wall -ansi	binary_tree.c			-o binary_tree.o


binary_tree_print.o:	binary_tree_print.c  binary_tree.h  error.h
			gcc -c -Wall -ansi	binary_tree_print.c		-o binary_tree_print.o


error.o:		error.c
			gcc -c -Wall -ansi	error.c


stack.o:		stack.c  stack.h  error.h
			gcc -c -Wall -ansi	stack.c				-o stack.o


process_input.o:	process_input.c  stack.h  error.h
			gcc -c -Wall -ansi	process_input.c			-o process_input.o


clean:
			rm *~  *.o

