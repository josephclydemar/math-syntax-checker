CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
INCLUDES = -I include
LDFLAGS =

BUILD_MODE =
RUN_COMMAND =

RAYLIB_LIB_PATH =

BUILD_BIN_DIR = build/bin
BUILD_OBJ_DIR = build/obj

BIN_TARGET_EXT = 
OBJ_TARGET_EXT = o

ifeq ($(OS), Windows_NT)
	BIN_TARGET_EXT = exe
	RAYLIB_LIB_PATH = libs/external/raylib/windows
else
	BIN_TARGET_EXT = out
	RAYLIB_LIB_PATH = libs/external/raylib/linux
endif

ifeq ($(BUILD_MODE), DEBUG)
	CFLAGS += -g
else
	CFLAGS += -O3
endif

LDFLAGS = -L $(RAYLIB_LIB_PATH) -lraylib

# header files
CORE_NODE_H = include/core/node.h
CORE_PATH_H = include/core/path.h

# source files
MAIN_SRC = src/main.c
CORE_NODE_SRC = src/core/node.c
CORE_PATH_SRC = src/core/path.c

# executable target file
BIN_TARGET = $(BUILD_BIN_DIR)/dfa.$(BIN_TARGET_EXT)

# relocatable target files
OBJ_MAIN_TARGET = $(BUILD_OBJ_DIR)/main.$(OBJ_TARGET_EXT)
OBJ_CORE_NODE_TARGET = $(BUILD_OBJ_DIR)/node.$(OBJ_TARGET_EXT)
OBJ_CORE_PATH_TARGET = $(BUILD_OBJ_DIR)/path.$(OBJ_TARGET_EXT)


ifeq ($(OS), Windows_NT)
	RUN_COMMAND = PATH=$(RAYLIB_LIB_PATH) $(BIN_TARGET)
else
	RUN_COMMAND = LD_LIBRARY_PATH=$(RAYLIB_LIB_PATH) $(BIN_TARGET)
endif


all: $(BIN_TARGET)

run: $(BIN_TARGET)
	@$(RUN_COMMAND)

clean:
	$(RM) $(BUILD_BIN_DIR)/*.$(BIN_TARGET_EXT)
	$(RM) $(BUILD_OBJ_DIR)/*.$(OBJ_TARGET_EXT)


$(BIN_TARGET): $(OBJ_MAIN_TARGET) $(OBJ_CORE_NODE_TARGET) $(OBJ_CORE_PATH_TARGET)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


$(OBJ_MAIN_TARGET): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJ_CORE_NODE_TARGET): $(CORE_NODE_SRC) $(CORE_NODE_H)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJ_CORE_PATH_TARGET): $(CORE_PATH_SRC) $(CORE_PATH_H)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
