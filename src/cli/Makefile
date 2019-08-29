CXX      := g++
CXXFLAGS := -Wall -std=c++17
LDFLAGS  := -lconfig++ -lstdc++fs -lwiringPi
OBJ_DIR  := ./obj-pc
APP_DIR  := ./
TARGET   := program
INCLUDE  := -I./ -I../ad9850 -I../common
SRC      := $(wildcard *.cpp) \
	$(wildcard ../ad9850/*.cpp) \
	$(wildcard ../common/*.cpp) \


OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/$(TARGET)
