# Mandatory compilation flags
CFLAGS = -Wall -pedantic -std=gnu99

# Unlinked object files used when compiling
SUPPORT_LIB = nodeLib.o cardLib.o

.PHONY := clean all
.DEFAULT_GOAL := all

all: clean node

node : main.c $(SUPPORT_LIB)
	gcc main.c $(SUPPORT_LIB) $(CFLAGS) -o node

# Files used in the support library
nodeLib.o : nodeLib.c
	gcc nodeLib.c $(CFLAGS) -c -o nodeLib.o

cardLib.o : cardLib.c
	gcc cardLib.c $(CFLAGS) -c -o cardLib.o
# Removing the object files
clean :
	rm -rf *.o

# Removing the compiled binaries
delete :
	rm -rf node