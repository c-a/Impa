CPP = g++
CPPFLAGS = -g -Wall -std=c++03

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROGRAMS = graph

all: $(PROGRAMS)

PROBLEMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all
.PHONY: clean
