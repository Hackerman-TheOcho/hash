.PHONY: debug clean all

CFLAGS += -std=c18 -Wall -Wextra -Wpedantic -Wwrite-strings -Wvla -Wfloat-equal -Waggregate-return

SRC_DIR := src
OBJ_DIR := obj

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
BIN := ht

all: $(BIN)

debug: CFLAGS += -g
debug: $(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
