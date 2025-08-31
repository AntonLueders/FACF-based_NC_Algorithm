all: ABPBDall

CC=gcc
OPT2=-Wextra -std=c99 -march=native -O3 -flto -ffast-math -fno-finite-math-only -fno-unsafe-math-optimizations -fno-align-functions -fno-align-jumps -fno-align-loops -fno-align-labels
OPT1=-Wall -std=c99 -g
LIBS3= -lgsl -lgslcblas -lm

ABPBDall: ABPBD.c
	${CC} ${OPT2} ${LIBS3} -c lists.c
	${CC} ${OPT2} ${LIBS3} -c ABPBD.c
	${CC} ${OPT2} ${LIBS3} -c distance.c
	${CC} ${OPT2} ${LIBS3} -c init.c
	${CC} ${OPT2} ${LIBS3} -c bd.c
	${CC} ${OPT2} ${LIBS3} -c printdata.c
	${CC} ${OPT2} ${LIBS3} -c inputdata.c
	${CC} ${OPT2} ${LIBS3} -c printdisplay.c
	${CC} ${OPT2} ${LIBS3} -c calc.c
	${CC} ${OPT2} ${LIBS3} -c force.c
	${CC} ${OPT2} ${LIBS3} lists.o distance.o init.o bd.o printdata.o inputdata.o printdisplay.o calc.o force.o ABPBD.o -o ABPBD.out ${LIBS3}
	
clean:
	rm -f lists.o
	rm -f ABPBD.o
	rm -f distance.o
	rm -f init.o
	rm -f bd.o
	rm -f printdata.o
	rm -f force.o
	rm -f inputdata.o
	rm -f printdisplay.o
	rm -f calc.o
	rm -f ABPBD.out
