TARGET = bin/petty
BUILD_DIR = build
LIBS = -lm
CC = gcc
CFLAGS = -g3 -Wall

.PHONY: default all clean dev

default: $(TARGET)
all: dev default

dev: CFLAGS += -DLOG_LEVEL=3 -g
dev: $(TARGET)

OBJECTS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

$(BUILD_DIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f $(BUILD_DIR)/*.o
	-rm -f $(TARGET)