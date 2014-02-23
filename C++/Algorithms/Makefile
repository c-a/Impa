CXX = g++
CPPFLAGS = -g -Wall -std=c++11

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROGRAMS = geometry graph disjoint-set

all: $(PROGRAMS)

%.o: %.cpp %.h
	$(CXX) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all
.PHONY: clean
