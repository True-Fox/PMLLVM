SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = main.c $(SRC_DIR)/vm.c $(SRC_DIR)/instructions.c
OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/vm.o $(OBJ_DIR)/instructions.o
CC_FLAGS = -Wall -Wextra -g -std=c11 -I$(INCLUDE_DIR)
CC = gcc
EXEC = pmllvm

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(CC_FLAGS) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/main.o: main.c $(INCLUDE_DIR)/vm.h $(INCLUDE_DIR)/program.h
	$(CC) $(CC_FLAGS) -c main.c -o $@

$(OBJ_DIR)/vm.o: $(SRC_DIR)/vm.c $(INCLUDE_DIR)/vm.h $(INCLUDE_DIR)/program.h
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/vm.c -o $@

$(OBJ_DIR)/instructions.o: $(SRC_DIR)/instructions.c $(INCLUDE_DIR)/vm.h $(INCLUDE_DIR)/program.h $(INCLUDE_DIR)/instructions.h
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/instructions.c -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
