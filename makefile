labapp: labapp.o zoomrecs.o
	gcc -o labapp labapp.o zoomrecs.o

labapp.o: labapp.c
	gcc -g -c labapp.c

zoomrecs.o: zoomrecs.c
	gcc -g -c zoomrecs.c