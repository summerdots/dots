# File: Makefile
# Build system for Dots MVP. It compiles all components and links to dots_lang.

CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -ldl
OBJS = main.o start.o interpreter.o keyword.o keywordlist.o photolist.o

# Default target: compile everything into dots_lang
dots_lang: $(OBJS)
	$(CC) $(CFLAGS) -o dots_lang $(OBJS) $(LDFLAGS)

# Compile .c files to .o files
main.o: main.c start.h
start.o: start.c start.h interpreter.h keywordlist.h
interpreter.o: interpreter.c interpreter.h photolist.h
keyword.o: keyword.c keyword.h photolist.h keywordlist.h
keywordlist.o: keywordlist.c keywordlist.h photolist.h
photolist.o: photolist.c photolist.h

# Clean all build output
clean:
	rm -f *.o dots_lang *.so .compile_error.log .keywords.mem

.PHONY: clean

