CC = gcc
CFLAGS = -g -Wall

CPP = g++
CPPFLAGS = -g -Wall

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROBLEMS = uva-10008 uva-400 uva-481 uva-583 uva-484 uva-514 uva-489 uva-10036 uva-10074 uva-11792
	uva-11753 uva-10226 uva-11235

all: $(PROBLEMS)

PROGRAMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

uva-11753: uva-11753.o
	$(CPP) -o uva-11753 uva-11753.o $(LDFLAGS) $(LIBS)

uva-10226: uva-10226.o
	$(CPP) -o uva-10226 uva-10226.o $(LDFLAGS) $(LIBS)

uva-11235: uva-11235.o
	$(CPP) -o uva-11235 uva-11235.o $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

.cpp.o :
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: all
.PHONY: count
.PHONY: clean
