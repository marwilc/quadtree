# Makefile
CFLAGS=-c -Wall 

# Variables
CC = g++
EJECUTABLE = quadtree

# Programa Principal
all: nodeQ.h quadTree.h quadtree.cpp
	$(CC) -o $(EJECUTABLE) quadtree.cpp 


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE) 
