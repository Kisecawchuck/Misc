# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -std=c11

# Linker flags
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# Source files
SRC = src/main.c src/glad.c  # Add all your .c files here
OBJ = $(SRC:.c=.o)

# Output binary name
TARGET = main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
