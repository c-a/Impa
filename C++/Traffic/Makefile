CPP = g++
WARNFLAGS = -Wall -Wextra --Wno-write-strings -Wno-sign-compare
CPPFLAGS = -g -Wall -Wno-write-strings -std=c++11
LDFLAGS = -Wl,-rpath,/usr/local/lib

PROBLEMS = uva-10449

all: $(PROBLEMS)

PROBLEMS: $@.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CPP) -o $@ -c $(CPPFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o $(PROBLEMS)

.PHONY: all
.PHONY: clean
