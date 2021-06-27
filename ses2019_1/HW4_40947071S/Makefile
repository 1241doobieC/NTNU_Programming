all:hw04_function.o
	gcc hw0401.c hw04_function.o -o hw0401
	gcc hw0402-1.c hw04_function.o -o hw0402-1
	gcc hw0402-2.c hw04_function.o -o hw0402-2
	gcc hw0403.c hw04_function.o -o hw0403
	gcc hw0404.c hw04_function.o -o hw0404
	gcc hw0405.c hw04_function.o -o hw0405

hw04_function.o:hw04_function.c
	gcc -c hw04_function.c -o hw04_function.o
clean:
	rm -rf hw0401
	rm -rf hw0402-1
	rm -rf hw0402-2
	rm -rf hw0403
	rm -rf hw0404
	rm -rf hw0405
	rm -rf hw04_function.o
