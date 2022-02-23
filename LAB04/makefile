lab2:	main.o Bibsim.o 
	gcc main.c Bibsim.c -o LAB4

main.o:	main.c
	gcc -c main.c

Bibsim.o: Bibsim.c sim.h
	gcc -c Bibsim.c

run:
	./lab4 input.txt

clear:
	rm -rf *.exe
	rm -rf *.om
	rm -rf *.o