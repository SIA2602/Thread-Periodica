CFLAGS = -Wall -g -lpthread -lrt
PROGS = main

g++: main.cpp
	$@ $^ -o $(PROGS) $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(PROGS)

install:
	cp $(PROGS) $(TARGETDIR)/bin