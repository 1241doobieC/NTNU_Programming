all:bignum.o mixed.o

		gcc hw0201.c mixed.o -o hw0201
		gcc hw0202.c -o hw0202
		gcc hw0203.c -o hw0203
		gcc sample.c bignum.o -o hw0204
		gcc hw0205.c -o hw0205

bignum:
		gcc -c bignum.c -o bignum.o
mixed:
		gcc -c mixed.c -o mixed.o
clean:
		rm -rf hw0201
		rm -rf hw0202
		rm -rf hw0203
		rm -rf hw0204
		rm -rf hw0205
