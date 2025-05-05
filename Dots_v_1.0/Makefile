
CC=gcc
CFLAGS=-Wall -Wextra -O2 -fPIC
OBJS=main.o interpreter.o scriptlist.o builtin.o memory.o instruction.o heart.o behaviortable.o

all: dots

dots: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f *.o dots
