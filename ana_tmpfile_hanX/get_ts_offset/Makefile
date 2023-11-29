out = analysis

sourcefile = main.cpp analysis.h analysis.cpp set.h

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs) -lSpectrum

CFLAGS = -g -Wall -std=c++11 -O2 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

GXX = g++

all:$(out)

$(out): $(sourcefile1)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -o $@ $(filter %.cpp ,$(sourcefile)) $(ROOTLIBS)

clean:
	rm -f *~ *.o $(out)
