CPP = g++
CPPFLAGS = -g -Wall -std=c++11 -Wno-write-strings

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROBLEMS = uva-673

all: $(PROBLEMS)

PROBLEMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: all
.PHONY: clean
