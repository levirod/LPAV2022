lab1:	main.o Biblist.o 
	gcc main.c Biblist.c -o LAB1

main.o:	main.c
	gcc -c main.c

Biblist.o: Biblist.c list.h
	gcc -c Biblist.c

run:
	./lab1 eventos.txt

clear:
	rm -rf *.exe
	rm -rf *.om
	rm -rf *.o
	