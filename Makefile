# TODO fix makefile
CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib  -lstdc++ -lstdc++fs -lm 
OBJ_DIR  := ./obj
APP_DIR  := ./build
TARGET   := cache-sim
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.cc)

depend: .depend

OBJECTS  := $(SRC:%.cc=$(OBJ_DIR)/%.o)

DEPS := $(OBJECTS:.o=.d)

-include $(DEPS)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cc $(HEAD_DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MF $(patsubst %.o,%.d,$@) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

debugv: CXXFLAGS += -DDEBUG_VERBOSE
debugv: debug

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*


