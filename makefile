HEADERSDIR = include
SRCDIR = src
BINDIR = bin
FLAGS = -Wall
P_THREADS = -lpthread
EXEC = awget ss

all:	$(EXEC)	

awget:	$(HEADERSDIR)/awget.h $(BINDIR)/chaindata.o $(BINDIR)/ss.o $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/main.o $(BINDIR)/ipportpair.o
	g++ $(FLAGS) $(P_THREADS) $(BINDIR)/ss.o $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/main.o $(BINDIR)/chaindata.o $(BINDIR)/ipportpair.o -o awget

ss:	$(HEADERSDIR)/ss.h $(BINDIR)/ss.o $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/chaindata.o $(BINDIR)/SSmain.o
	g++ $(FLAGS) $(P_THREADS) $(BINDIR)/ss.o $(BINDIR)/SSmain.o $(BINDIR)/chaindata.o $(BINDIR)/ipportpair.o $(BINDIR)/reader.o $(BINDIR)/usage.o -o ss

$(BINDIR)/SSmain.o:	$(SRCDIR)/SSmain.cpp $(HEADERSDIR)/p2.h $(BINDIR)/ss.o $(BINDIR)/reader.o $(BINDIR)/usage.o $(BINDIR)/chaindata.o
	g++ $(FLAGS) $(P_THREADS) -I$(HEADERSDIR) $(SRCDIR)/SSmain.cpp -c -o $(BINDIR)/SSmain.o

$(BINDIR)/main.o:	$(SRCDIR)/main.cpp $(HEADERSDIR)/p2.h $(BINDIR)/reader.o $(BINDIR)/usage.o
	g++ $(FLAGS) $(P_THREADS) -I$(HEADERSDIR) $(SRCDIR)/main.cpp -c -o $(BINDIR)/main.o

$(BINDIR)/reader.o:	$(SRCDIR)/reader.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/reader.h $(BINDIR)/usage.o $(BINDIR)/ss.o
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/reader.cpp -c -o $(BINDIR)/reader.o

$(BINDIR)/ss.o:	$(SRCDIR)/ss.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/ss.h $(BINDIR)/chaindata.o
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/ss.cpp -c -o $(BINDIR)/ss.o

$(BINDIR)/usage.o:	$(SRCDIR)/usage.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/usage.h
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/usage.cpp -c -o $(BINDIR)/usage.o

$(BINDIR)/chaindata.o:	$(SRCDIR)/chaindata.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/chaindata.h $(BINDIR)/ipportpair.o
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/chaindata.cpp -c -o $(BINDIR)/chaindata.o

$(BINDIR)/ipportpair.o:	$(SRCDIR)/ipportpair.cpp $(HEADERSDIR)/p2.h $(HEADERSDIR)/ipportpair.h
	g++ $(FLAGS) -I$(HEADERSDIR) $(SRCDIR)/ipportpair.cpp -c -o $(BINDIR)/ipportpair.o

clean:
	rm awget
	rm ss
	rm -rf bin/
	mkdir bin