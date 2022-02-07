CXX=g++
CXXFLAGS=-std=c++17

# Extensions of files to delete when cleaning
CLEANEXTS   = o a

# target file and the install directory
OUTPUTFILE  = falib.a
INSTALLDIR  = ../binaries

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libjohnpaul.a from john.o, paul.o, and johnpaul.o
$(OUTPUTFILE): fa.o
	ar ru $@ $^
	ranlib $@

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done

# Indicate dependencies of .ccp files on .hpp files
fa.o: FA.cpp FA.h
