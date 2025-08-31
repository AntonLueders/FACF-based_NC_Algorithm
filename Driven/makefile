all: HSBDall

CC=gcc
OPT2=-Wextra -std=c99 -march=native -O3 -flto -ffast-math -fno-finite-math-only -fno-unsafe-math-optimizations -fno-align-functions -fno-align-jumps -fno-align-loops -fno-align-labels
OPT1=-Wall -std=c99 -g
LIBS3= -lgsl -lgslcblas -lm

HSBDall: HSBD.c
	${CC} ${OPT2} ${LIBS3} -c lists.c
	${CC} ${OPT2} ${LIBS3} -c HSBD.c
	${CC} ${OPT2} ${LIBS3} -c distance.c
	${CC} ${OPT2} ${LIBS3} -c init.c
	${CC} ${OPT2} ${LIBS3} -c bd.c
	${CC} ${OPT2} ${LIBS3} -c printdata.c
	${CC} ${OPT2} ${LIBS3} -c verletlist.c
	${CC} ${OPT2} ${LIBS3} -c inputdata.c
	${CC} ${OPT2} ${LIBS3} -c printdisplay.c
	${CC} ${OPT2} ${LIBS3} -c calc.c
	${CC} ${OPT2} ${LIBS3} lists.o distance.o init.o bd.o printdata.o verletlist.o inputdata.o printdisplay.o calc.o HSBD.o -o HSBD.out ${LIBS3}
	
clean:
	rm -f lists.o
	rm -f HSBD.o
	rm -f distance.o
	rm -f init.o
	rm -f bd.o
	rm -f printdata.o
	rm -f verletlist.o
	rm -f inputdata.o
	rm -f printdisplay.o
	rm -f calc.o
	rm -f HSBD.out
