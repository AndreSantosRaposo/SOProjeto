CC = gcc
OBJS = main.o validator.o miner.o statistics.o
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

main.o: main.c includes.h
validador.o: validator.c includes.h
miner.o: miner.c includes.h 
statistics.o: statistics.c