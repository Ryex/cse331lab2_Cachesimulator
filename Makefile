IDIR =./include
SDIR=./src
CC=g++
CXXFLAGS=


_DEPS = cachesim.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cachesim.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS=

ODIR=obj


all: cachesim

$(ODIR):
	mkdir $(ODIR)

$(ODIR)/%.o: $(ODIR) $(SDIR)/%.cc $(DEPS) 
	$(CC) -c -o $@ $< $(CXXFLAGS)

cachesim: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ cachesim
	rmdir $(ODIR)


