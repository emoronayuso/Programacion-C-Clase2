NAME=concesionario.out
BIN_DIR=bin


all: build ${NAME}

${NAME}: ${BIN_DIR}/concesionario.o ${BIN_DIR}/coche.o main.c
	     gcc ${BIN_DIR}/coche.o ${BIN_DIR}/concesionario.o main.c -o ${NAME} 

${BIN_DIR}/concesionario.o: concesionario.c concesionario.h
	     gcc -c concesionario.c -o ${BIN_DIR}/concesionario.o

${BIN_DIR}/coche.o: coche.c coche.h
	     gcc -c coche.c -o ${BIN_DIR}/coche.o

build:
	mkdir bin

clean:
	rm -rf bin
