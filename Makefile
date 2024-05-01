# ==================================================== #
#          C O M P I L A T I O N   S E T U P           #
# ==================================================== #
#            defines the compiler and flags            #
# ---------------------------------------------------- #


CC = gcc 
CFLAGS = -g -W -Wall -std=c99 -pedantic -O2
CLIBS = -lm


# ==================================================== #
#         T A R G E T S   D E C L A R A T I O N        #
# ==================================================== #
# 		   defines the targets of the makefile         #
# ---------------------------------------------------- #

all: build simple-clean

build: main.o ensemble.o afn.o
	$(CC) main.o ensemble.o afn.o -o main $(CLIBS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c

ensemble.o: ./src/ensemble/ensemble.c
	$(CC) $(CFLAGS) -c ./src/ensemble/ensemble.c

afn.o: ./src/afn/afn.c
	$(CC) $(CFLAGS) -c ./src/afn/afn.c

simple-clean:
	rm -f *.o

clean:
	rm -f *.o main