CC = gcc
OBJS = main.o validator.o 
PROG = main
FLAGS = -Wall -g

# Generic
all: ${PROG}

clean:
	rm -f ${OBJS} *~ ${PROG}

${PROG}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o $@

.c.o:
	${CC} ${FLAGS} -c $< -o $@

main.o: main.c funcoes.h
validador.o: validator.c
