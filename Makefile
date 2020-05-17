# MAKEFILE for ASSIGNMENT 4 of C++
#   by Tim Müller (11774606)


##### CONSTANTS #####

GXX = g++
GXX_ARGS = -std=c++17 -O2 -Wall -Wextra

SRC=src
LIB=$(SRC)/lib
BIN=bin
OBJ=$(BIN)/obj
TST_SRC=tests
TST_BIN=$(BIN)/tests

# Add the includes
GXX_ARGS += -I$(LIB)/include

# By default, set to use the LargeNumber lib
NUMBERS_LIB=$(OBJ)/LargeNumber.o



##### OPTIONS #####
ifdef DEBUG
GXX_ARGS += -DDEBUG -g
endif

ifdef SMALLNUMBER
GXX_ARGS += -DSMALLNUMBER
NUMBERS_LIB = $(OBJ)/SmallNumber.o
endif

ifdef TEST
GXX_ARGS += -DTEST
endif



##### DA RULES #####

# Meta
.PHONY: all main dirs tests clean
default: all

# Folders
$(BIN):
	mkdir -p $@
$(OBJ): $(BIN)
	mkdir -p $@
$(TST_BIN): $(BIN)
	mkdir -p $@

# General object rules
$(OBJ)/%.o: $(LIB)/%.cpp | $(OBJ)
	$(GXX) $(GXX_ARGS) -o $@ -c $<

# The Numbers static library
$(OBJ)/Numbers.a: $(OBJ)/Number.o $(OBJ)/Math.o
	ar rvs $@ $(OBJ)/Number.o $(OBJ)/Math.o

# Compile main
$(OBJ)/Main.o: $(SRC)/Main.cpp | $(OBJ)
	$(GXX) $(GXX_ARGS) -o $@ -c $<

# Link everything together, either as LargeNumber or SmallNumber
$(BIN)/main.out: $(OBJ)/Main.o $(NUMBERS_LIB) $(OBJ)/Numbers.a
	$(GXX) $(GXX_ARGS) -o $@ $(OBJ)/Main.o $(NUMBERS_LIB) $(OBJ)/Numbers.a

# Main meta rule
main: $(BIN)/main.out

# Test rule for LinkedLists
$(TST_BIN)/test_linkedlist.out: $(TST_SRC)/test_linkedlist.cpp $(OBJ)/LinkedList.o | $(TST_BIN)
	$(GXX) $(GXX_ARGS) -o $@ $(TST_SRC)/test_linkedlist.cpp $(OBJ)/LinkedList.o

# Test rule for LargeNumber
$(TST_BIN)/test_largenumber.out: $(TST_SRC)/test_largenumber.cpp $(OBJ)/LargeNumber.o $(OBJ)/Number.o $(OBJ)/LinkedList.o | $(TST_BIN)
	$(GXX) $(GXX_ARGS) -o $@ $(TST_SRC)/test_largenumber.cpp $(OBJ)/LargeNumber.o $(OBJ)/Number.o $(OBJ)/LinkedList.o

# Test pseudo rule
tests: $(TST_BIN)/test_linkedlist.out $(TST_BIN)/test_largenumber.out
	$(info )
	$(info Running tests...)
	$(info )

	$(TST_BIN)/test_linkedlist.out
	$(TST_BIN)/test_largenumber.out

# All and clean
all: tests main

clean:
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*.out

	rm -rf $(TST_BIN)/*.out
