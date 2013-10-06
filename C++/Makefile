
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall

CPP = g++
CPPFLAGS = -g -Wall

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: uva-10008 uva-400 uva-481 uva-583 uva-484 uva-514 uva-489 uva-10036 uva-10074 uva-11792

uva-10008: uva-10008.o
	$(CC) -o uva-10008 uva-10008.o $(LDFLAGS) $(LIBS)

uva-400: uva-400.o
	$(CPP) -o uva-400 uva-400.o $(LDFLAGS) $(LIBS)

uva-481: uva-481.o
	$(CPP) -o uva-481 uva-481.o $(LDFLAGS) $(LIBS)

uva-583: uva-583.o
	$(CPP) -o uva-583 uva-583.o $(LDFLAGS) $(LIBS)

uva-484: uva-484.o
	$(CPP) -o uva-484 uva-484.o $(LDFLAGS) $(LIBS)

uva-514: uva-514.o
	$(CPP) -o uva-514 uva-514.o $(LDFLAGS) $(LIBS)

uva-489: uva-489.o
	$(CPP) -o uva-489 uva-489.o $(LDFLAGS) $(LIBS)

uva-10036: uva-10036.o
	$(CPP) -o uva-10036 uva-10036.o $(LDFLAGS) $(LIBS)

uva-10074: uva-10074.o
	$(CPP) -o uva-10074 uva-10074.o $(LDFLAGS) $(LIBS)

uva-11792: uva-11792.o
	$(CPP) -o uva-11792 uva-11792.o $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

.cpp.o :
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
