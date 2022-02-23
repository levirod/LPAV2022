lab2:	main.o Bibhash.o 
	gcc main.c Bibhash.c -o LAB2

main.o:	main.c
	gcc -c main.c

Bibhash.o: Bibhash.c hash.h
	gcc -c Bibhash.c

# Tamanho da tabela Hash Alterar argumento no run #

run:
	./lab2 100 entradas.txt

clear:
	rm -rf *.exe
	rm -rf *.om
	rm -rf *.o