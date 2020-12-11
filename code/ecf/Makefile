csapp:
	gcc -c ../src/csapp.c -I ../include -o obj/csapp.o

signal1:
	gcc -c signal1.c -o ./obj/signal1.o -I ../include 
	gcc -o ./bin/signal1 ./obj/signal1.o ./obj/csapp.o -lpthread

signal2:
	gcc -c signal2.c -o ./obj/signal2.o -I ../include 
	gcc -o ./bin/signal2 ./obj/signal2.o ./obj/csapp.o -lpthread

signalprob0:
	gcc -c signalprob0.c -o ./obj/signalprob0.o -I ../include 
	gcc -o ./bin/signalprob0 ./obj/signalprob0.o ./obj/csapp.o -lpthread

procmask2:
	gcc -c procmask2.c -o ./obj/procmask2.o -I ../include 
	gcc -o ./bin/procmask2 ./obj/procmask2.o ./obj/csapp.o -lpthread

.PHONY : clean 
clean:
	rm -rf ./obj/*.o
	rm -rf ./bin/*
