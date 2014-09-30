HEADERSDIR = include
SRCDIR = src
BINDIR = bin
FLAGS = -Wall
EXEC = awget

all:	$(EXEC)	

awget:	$(HEADERSDIR)/awget.h $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/main.o
	g++ $(FLAGS) $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/main.o -o awget

$(BINDIR)/main.o:	$(SRCDIR)/main.cpp $(HEADERSDIR)/p2.h $(BINDIR)/reader.o $(BINDIR)/usage.o
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/main.cpp -c -o $(BINDIR)/main.o

$(BINDIR)/reader.o:	$(SRCDIR)/reader.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/reader.h $(BINDIR)/usage.o
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/reader.cpp -c -o $(BINDIR)/reader.o

$(BINDIR)/usage.o:	$(SRCDIR)/usage.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/usage.h
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/usage.cpp -c -o $(BINDIR)/usage.o

clean:
	rm -rf bin/
	mkdir bin