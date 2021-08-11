CFLAGS = -Wall -g -lpthread -lrt
PROGS = main

g++: main.cpp thread.h thread.cpp
	$@ $^ -o $(PROGS) $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(PROGS)

install:
	cp $(PROGS) $(TARGETDIR)/bin