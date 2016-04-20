# Use this under Unix with command "make".

CFLAGS=-O3 -Wall
LDADD=

infimnist: main.o infimnist.o
	${CC} ${CFLAGS} -o $@ main.o infimnist.o ${LDADD}

infimnist.o: infimnist.c infimnist.h
	${CC} ${CFLAGS} -c infimnist.c

main.o: main.c infimnist.h
	${CC} ${CFLAGS} -c main.c

clean: FORCE
	-rm main.o infimnist.o >/dev/null
	-rm infimnist >/dev/null

FORCE:
