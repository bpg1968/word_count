# Generic Makefile

# directory for header files
IDIR=include

# directory for object files
ODIR=../obj

# directory for executable file
BDIR=../bin

# directory for library files (not used at the moment)
LDIR=.

_DEPS=wc.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=wc.o process_line.o count_chars.o count_words.o usage.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_TARGET=wc
TARGET=$(patsubst %,$(BDIR)/%,$(_TARGET))

# the compiler:
#   `gcc` for C program
#   `g++` for C++
#   `mpicc` for C program using MPI
#   `mpic++` for C++ program using MPI
CC=gcc

# compiler flags:
#   `-Wall` tuns on most compiler warnings
#   `-g` adds debugging information to the executable file
#   `-pthread` to use the Pthreads library
#   `-I$(IDIR)` specify a path to header files
CFLAGS=-Wall -pthread -I$(IDIR)

# move files
MV=mv

# remove files
RM=rm

all: $(TARGET)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# just in case we have a file named 'clean'
.PHONY: clean

clean:
	$(RM) $(OBJ) $(TARGET)

