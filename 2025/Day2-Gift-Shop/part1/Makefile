# Makefile
CXX := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2 -g
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
DEPS := $(SRC:.cpp=.d)
TARGET := main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ) $(DEPS)

.PHONY: all clean