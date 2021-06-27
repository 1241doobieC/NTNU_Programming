all: hw06_functions.o
	gcc hw0601.c -o hw0601
	gcc hw0602.c hw06_functions.o -o hw0602 -lm
	gcc hw0603.c hw06_functions.o -o hw0603 -lm
	gcc hw0604.c hw06_functions.o -o hw0604 -lm
	gcc hw0605.c hw06_functions.o -o hw0605 -lm

hw06_function.o:hw06_functions.c
	gcc -c hw06_functions.c -o hw06_functions.o
clean:
	rm -rf hw0601
	rm -rf hw0602
	rm -rf hw0603
	rm -rf hw0604
	rm -rf hw0605
