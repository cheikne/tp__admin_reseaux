all:tp1.e

tp1.e: tp1.o main.o
	gcc tp1.o main.o -o tp1.e
tp1.o:tp1.c
	gcc -c tp1.c

main.o:main.c
	gcc -c main.c
