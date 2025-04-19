# Makefile for building a Raylib project with clang

# Compiler and flags
CC = clang
CFLAGS = -Iinclude -Werror -Wall -g
LDFLAGS = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a

# Source files and target
SRC = $(wildcard *.c)
TARGET = liquid.out

# Default build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)

