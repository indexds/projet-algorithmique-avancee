# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra
PKG_CONFIG = pkg-config
GTK4_CFLAGS = $(shell $(PKG_CONFIG) --cflags gtk4)
GTK4_LIBS = $(shell $(PKG_CONFIG) --libs gtk4)

# Target executable
TARGET = main

# Source files
SRCS = parser.c inferrer.c app.c main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)
	@echo "Compilation finished."

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) -o $@ $^ $(GTK4_LIBS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) $(GTK4_CFLAGS) -c $< -o $@

# Dependencies
parser.o: parser.h
inferrer.o: inferrer.h
app.o: app.h
main.o: parser.h inferrer.h app.h

# Clean rule to remove generated object files
clean:
	rm -f $(OBJS)
	@echo "Object files cleaned."
