SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) main.c
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))
OBJ_FILES += $(OBJ_DIR)/lex.yy.o $(OBJ_DIR)/y.tab.o

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -I$(INCLUDE_DIR)
LDFLAGS = -lm

EXEC = pmllvm

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

# Ensure parser is generated before the lexer
$(OBJ_DIR)/y.tab.o: $(OBJ_DIR)/y.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/lex.yy.o: $(OBJ_DIR)/lex.yy.c $(OBJ_DIR)/y.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate lexer and parser
$(OBJ_DIR)/y.tab.c $(OBJ_DIR)/y.tab.h: $(SRC_DIR)/parser.y
	bison -d -o $(OBJ_DIR)/y.tab.c $<

$(OBJ_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(OBJ_DIR)/y.tab.h
	flex -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
