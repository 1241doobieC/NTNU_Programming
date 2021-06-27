all:myprintf.o
	gcc hw0401.c -o hw0401 -lm
	gcc hw0402.c -o hw0402
	gcc hw0403.c myprintf.o -o hw0403
	gcc hw0404.c -o hw0404

myprintf:
	gcc -c myprintf.c -o myprintf.o
clean:
	rm -rf hw0401 
	rm -rf hw0402
	rm -rf hw0403
	rm -rf hw0404