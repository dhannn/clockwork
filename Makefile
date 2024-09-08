# Compiler Information
CC=g++
CFLAGS=-Wall -g 
EXEC=.exe

# Directories

BIN_DIR=bin
BIN=$(BIN_DIR)/cw$(EXEC)

DOC_DIR=docs
DOCS=$(wildcard $(docs)/*)

SOURCES=$(wildcard $(SRC_DIR)/**/*.cpp)
SRC_DIR=src

HEADERS = $(wildcard $(SRC_DIR)/**/*.hpp)

OBJ_DIR=obj
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

TEST_DIR=test
TEST_BIN_DIR=$(TEST_DIR)/bin
TEST_FRAMEWORK=$(TEST_DIR)/ceemply/ceemply.c


MAIN_SRC=$(SRC_DIR)/main.cpp

all: $(BIN)

$(BIN): $(OBJECTS)
	if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CC) $(CFLAGS) $(MAIN_SRC) $? -o $(BIN)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifneq (, $(wildcard $(BIN_DIR)))
	rmdir /S /q $(BIN_DIR)
else 
	$(info > Binary executable already deleted)
endif

ifneq (, $(wildcard $(OBJECTS)))
	rmdir /S /q $(OBJ_DIR)
else
	$(info > Object files already deleted)
endif

ifneq (, $(wildcard *.zip))
	del $(SUBMISSION)
else
	$(info > Submission already deleted)
endif


test: $(TEST_BINS)

test_%: $(OBJ_DIR)/%.o
	$(CC) $(CFLAGS) $(TEST_DIR)/$@.c $< $(TEST_FRAMEWORK) -o $(TEST_BIN_DIR)/$@

submit:
	minizip -o $(SUBMISSION) $(BIN) $(INCLUDES) $(HEADERS) $(OBJS) $(MAIN_SRC) $(INCLUDED_MISC_FILES)
