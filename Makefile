all:tp

tp: tp1.o tp2.o main.o
	gcc tp1.o tp2.o main.o -o tp
tp1.o:tp1.c
	gcc -c tp1.c
tp2.o:tp2.c
	gcc -c tp2.c

main.o:main.c
	gcc -c main.c
clean:
	rm -f *.o tp