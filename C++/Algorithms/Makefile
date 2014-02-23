CXX = g++
CPPFLAGS = -g -Wall -Wextra -Wno-sign-compare -std=c++11

INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PROGRAMS = bipartite geometry graph disjoint-set

all: $(PROGRAMS)

%.o: %.cpp %.h
	$(CXX) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all
.PHONY: clean
