lab3:	main.o Bibgrafos.o 
	gcc main.c Bibgrafos.c -o LAB3

main.o:	main.c
	gcc -c main.c

Bibgrafos.o: Bibgrafos.c grafos.h
	gcc -c Bibgrafos.c

run:
	./lab3 arquivo.txt

clear:
	rm -rf *.exe
	rm -rf *.om
	rm -rf *.o