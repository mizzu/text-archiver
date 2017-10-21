tarc: arcmain.o arc.o crt.o arcls.o
	gcc arcmain.o arc.o crt.o arcls.o -o tarc
arcmain.o: arcmain.c arc.h
	gcc -c arcmain.c
arc.o: arc.c arc.h
	gcc -c arc.c
crt.o: crt.c arc.h
	gcc -c crt.c
arcls.o: arcls.c arc.h
	gcc -c arcls.c
clean:
	rm -f *.o core
