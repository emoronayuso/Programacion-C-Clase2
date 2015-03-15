NAME=gestor_tareas.out
BIN_DIR=bin


all: build ${NAME}

${NAME}: ${BIN_DIR}/gestor_tareas.o ${BIN_DIR}/tarea.o main.c
	     gcc -g ${BIN_DIR}/tarea.o ${BIN_DIR}/gestor_tareas.o main.c -o ${NAME} 

${BIN_DIR}/gestor_tareas.o: gestor_tareas.c gestor_tareas.h
	     gcc -g -c gestor_tareas.c -o ${BIN_DIR}/gestor_tareas.o

${BIN_DIR}/tarea.o: tarea.c tarea.h
	     gcc -g -c tarea.c -o ${BIN_DIR}/tarea.o

build:
	mkdir bin

clean:
	rm -rf bin
