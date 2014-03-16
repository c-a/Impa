CPP = g++
WARNFLAGS = -Wall -Wextra -Wno-write-strings -Wno-sign-compare
CPPFLAGS = -g -std=c++11 $(WARNFLAGS)
LDFLAGS = -Wl,-rpath,/usr/local/lib

PROBLEMS = uva-10118

all: $(PROBLEMS)

PROBLEMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: all
.PHONY: clean
