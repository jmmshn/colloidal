#  Declare variables
CC=g++
CFLAGS=-c -Wall

all: coll

coll: main.o Particle.o
	$(CC) -Wall main.o Particle.o -o coll

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

particle.o: Particle.h Particle.cpp
	$(CC) $(CFLAGS) Particle.h particle.cpp

clean: 
	rm -rf *.o coll *~
