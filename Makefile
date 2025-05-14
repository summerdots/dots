# ==== Project Name ====
TARGET = dots
COMPILER = dotsc

# ==== Source Files ====
SRC = src/main.c \
      src/behavior.c \
      src/executor.c \
      src/builtin.c \
      src/control.c \
      src/lazy.c \
      src/mathmod.c \
      src/modio.c \
      src/introspect.c

# ==== Compiler Settings ====
CC = gcc
CFLAGS = -Wall -O2

# ==== Build Targets ====
all: $(TARGET) $(COMPILER)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(COMPILER): dotsc.c
	$(CC) $(CFLAGS) dotsc.c -o $(COMPILER)

compile-example: $(COMPILER)
	@mkdir -p modules
	./$(COMPILER) examples/hello.dots

clean:
	rm -f $(TARGET) $(COMPILER)
	rm -rf modules