all : main

library.o : library.c library.h
	gcc -c library.c

tests.o : tests.c tests.h library.o
	gcc -c tests.c

main: main.c library.o tests.o
	gcc -o main main.c tests.o library.o
	./main

doc: Doxyfile
	doxygen Doxyfile

clean:
	rm -f main *.o
	rm -fR documentation/