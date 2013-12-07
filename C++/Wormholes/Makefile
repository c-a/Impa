CPP = g++
CPPFLAGS = -g -Wall -std=c++03

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROBLEMS = uva-558

all: $(PROBLEMS)

PROBLEMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: all
.PHONY: clean
