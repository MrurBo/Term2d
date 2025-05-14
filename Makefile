CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS := 

# Library
LIB_NAME := term2d
LIB_DIR := lib
LIB_TARGET := $(LIB_DIR)/lib$(LIB_NAME).a

# Source files
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRCS))

# Test program
TEST_DIR := test
TEST_SRC := $(TEST_DIR)/test.cpp
TEST_TARGET := $(TEST_DIR)/test

.PHONY: all clean test

all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(LIB_TARGET)
	$(CXX) $(CXXFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) -o $@

clean:
	rm -f $(OBJS) $(LIB_TARGET) $(TEST_TARGET)

run: test
	$(TEST_TARGET)