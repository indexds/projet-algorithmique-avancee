# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra
PKG_CONFIG = pkg-config
GTK4_CFLAGS = $(shell $(PKG_CONFIG) --cflags gtk4)
GTK4_LIBS = $(shell $(PKG_CONFIG) --libs gtk4)

# Target executable
TARGET = main

# Source files
SRCS = parser.c inferrer.c app.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) -o $@ $^ $(GTK4_LIBS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)